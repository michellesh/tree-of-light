import React, { useEffect } from 'react';
import styled from 'styled-components';
import * as d3 from 'd3';

import { BACKGROUND_COLOR } from 'const';
import * as animations from 'animations';
import { useCanvas } from 'hooks';
import { pointOnEllipse, pointOnLine, radians } from 'utils';

window.d3 = d3;

const WIDTH = 1050;
const HEIGHT = 1050;
const ELLIPSE_RATIO = 0.5; // ratio of width/height for each ellipse
const ELLIPSE_MAX_WIDTH = 300; // width of widest ellipse on top in px
const DISTANCE_BETWEEN_DISCS = 100; // space between each disc in px
const NUM_STRIPS_PER_DISC = 16; // number of LED strips in each disc
const DEGREES_BETWEEN_STRIPS = 360 / NUM_STRIPS_PER_DISC;
const TOP_OFFSET = 160; // number of pixels offset from top of canvas

// Stick lengths are as follows (in ft).
// They should all start at the edge of a 24" diameter circle
// (meaning the lowest layer is 8' total diameter: 3+2+3).
const STICK_LENGTHS_FT = [12, 10.875, 9.75, 8.625, 7.5, 6.375, 5.25, 4.125, 3];
const NUM_LEDS_PER_FT = 3; // This is wrong, but just for testing
const INNER_RING_RADIUS_FT = 1;

const ftToPx = d3
  .scaleLinear()
  .domain([0, d3.max(STICK_LENGTHS_FT)])
  .range([0, ELLIPSE_MAX_WIDTH]);

const STICK_LENGTHS_PX = STICK_LENGTHS_FT.map(ftToPx);
const NUM_LEDS_PER_PX = NUM_LEDS_PER_FT / ftToPx(1);
const INNER_RING_RADIUS_PX = ftToPx(INNER_RING_RADIUS_FT);

const Container = styled.div`
  background-color: ${BACKGROUND_COLOR};
  height: 100%;
  text-align: center;
`;

const Ellipse = config => {
  const _ellipse = {
    ...config,
    rotation: 0,
    startAngle: radians(0),
    endAngle: radians(360)
  };
  return Object.freeze({
    ..._ellipse,
    draw: context => {
      const { x, y, rx, ry, rotation, startAngle, endAngle } = _ellipse;
      context.beginPath();
      context.ellipse(x, y, rx, ry, rotation, startAngle, endAngle);
      context.fillStyle = BACKGROUND_COLOR;
      context.fill();
      context.strokeStyle = 'black';
      context.stroke();
    }
  });
};

const LED = config => {
  const defaults = {
    color: 'black',
    endAngle: 2 * Math.PI,
    radius: 1,
    startAngle: 0
  };
  const _led = { ...defaults, ...config };
  return Object.freeze({
    ..._led,
    color: color => LED({ ..._led, color }),
    r: _led.radius,
    radius: radius => LED({ ..._led, radius }),
    resetColor: () => LED({ ..._led, color: defaults.color }),
    resetRadius: () => LED({ ..._led, radius: defaults.radius }),
    on: (color = 'white') => LED({ ..._led, radius: 3, color }),
    off: () => LED({ ..._led, radius: defaults.radius, color: defaults.color }),
    draw: context => {
      const { x, y, color, radius, startAngle, endAngle } = _led;
      context.beginPath();
      context.arc(x, y, radius, startAngle, endAngle);
      context.fillStyle = color;
      context.fill();
    }
  });
};

const DISCS = STICK_LENGTHS_PX.map((stickLengthPx, i) => {
  // Center point of disc
  const x = WIDTH / 2;
  const y = TOP_OFFSET + DISTANCE_BETWEEN_DISCS * i;

  // Outer ellipse
  const outerEllipse = Ellipse({
    x,
    y,
    rx: INNER_RING_RADIUS_PX / 2 + stickLengthPx,
    ry: (INNER_RING_RADIUS_PX / 2 + stickLengthPx) * ELLIPSE_RATIO
  });

  // Inner ellipse
  const innerEllipse = Ellipse({
    x,
    y,
    rx: INNER_RING_RADIUS_PX,
    ry: INNER_RING_RADIUS_PX * ELLIPSE_RATIO
  });

  const numLEDsInStrip = stickLengthPx * NUM_LEDS_PER_PX;

  const leds = d3.range(NUM_STRIPS_PER_DISC).map(stripNumber => {
    const r =
      radians(stripNumber * DEGREES_BETWEEN_STRIPS) +
      radians(DEGREES_BETWEEN_STRIPS / 2);
    const stripStart = pointOnEllipse(outerEllipse, r);
    const stripEnd = pointOnEllipse(innerEllipse, r);
    return d3
      .range(0, 1, 1 / numLEDsInStrip)
      .map(howFar => LED(pointOnLine(stripEnd, stripStart, howFar)));
  });

  return { outerEllipse, innerEllipse, leds };
});

console.log(
  'Total LED count:',
  DISCS.reduce((acc, disc) => acc + disc.leds.flatMap(x => x).length, 0)
);
console.log('DISCS', DISCS);

const Prototype = () => {
  const [canvasRef, context] = useCanvas();

  useEffect(() => {
    if (context) {
      // Draw the discs and LED dots
      DISCS.forEach(disc => {
        disc.outerEllipse.draw(context);
        disc.innerEllipse.draw(context);
        disc.leds.forEach(ledStrip =>
          ledStrip.forEach(led => led.draw(context))
        );
      });

      // Animate
      animations.juggle(context, DISCS);
    }
  }, [context]);

  return (
    <Container>
      <canvas ref={canvasRef} width={WIDTH} height={HEIGHT} />
    </Container>
  );
};

export default Prototype;
