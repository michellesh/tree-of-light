import React, { useEffect } from 'react';
import styled from 'styled-components';
import * as d3 from 'd3';

import { useCanvas } from 'hooks';
import { radians } from 'utils';

const WIDTH = 1000;
const HEIGHT = 1000;
const BACKGROUND_COLOR = 'white';
const ELLIPSE_RATIO = 0.5;
const ELLIPSE_MAX_WIDTH = 300;
const DISTANCE_BETWEEN_LEVELS = 100;

// Stick lengths are as follows (in ft).
// They should all start at the edge of a 24" diameter circle
// (meaning the lowest layer is 8' total diameter: 3+2+3).
const stickLengths = [12, 10.875, 9.75, 8.625, 7.5, 6.375, 5.25, 4.125, 3];
const widthScale = ELLIPSE_MAX_WIDTH / d3.max(stickLengths);

const Canvas = styled.canvas`
  border: 1px solid black;
  background-color: ${BACKGROUND_COLOR};
`;

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
      context.fillStyle = 'white';
      context.fill();
      context.strokeStyle = 'black';
      context.stroke();
    }
  });
};

const ELLIPSES = stickLengths.map((stickLength, level) =>
  Ellipse({
    x: WIDTH / 2,
    y: ELLIPSE_MAX_WIDTH * ELLIPSE_RATIO + DISTANCE_BETWEEN_LEVELS * level,
    rx: stickLength * widthScale,
    ry: stickLength * widthScale * ELLIPSE_RATIO
  })
);

const Prototype = () => {
  const [canvasRef, context] = useCanvas();

  useEffect(() => {
    if (context) {
      ELLIPSES.forEach(ellipse => ellipse.draw(context));
    }
  }, [context]);

  return (
    <Container>
      <Canvas ref={canvasRef} width={WIDTH} height={HEIGHT} />
    </Container>
  );
};

export default Prototype;
