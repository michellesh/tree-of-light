import * as d3 from 'd3';

import { WIDTH } from 'const';
import { Ellipse } from 'models/Ellipse';
import { LED } from 'models/LED';
import { distance, pointOnEllipse, pointOnLine, radians } from 'utils';

//const ELLIPSE_RATIO = 0.5; // ratio of width/height for each ellipse
const ELLIPSE_RATIO = 1; // ratio of width/height for each ellipse
const ELLIPSE_MAX_WIDTH = 300; // width of widest ellipse on top in px
const DISTANCE_BETWEEN_DISCS = 100; // space between each disc in px
const NUM_STRIPS_PER_DISC = 16; // number of LED strips in each disc
const NUM_PETALS_PER_DISC = 6;
const DEGREES_BETWEEN_STRIPS = 360 / NUM_STRIPS_PER_DISC;
const DEGREES_BETWEEN_PETALS = 360 / NUM_PETALS_PER_DISC;
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

const ELLIPSES = (stickLengthPx, index) => {
  // Center point of disc
  const x = WIDTH / 2;
  const y = TOP_OFFSET + DISTANCE_BETWEEN_DISCS * index;

  // Outer ellipse
  const outerEllipse = Ellipse({
    x,
    y,
    rx: INNER_RING_RADIUS_PX + stickLengthPx,
    ry: (INNER_RING_RADIUS_PX + stickLengthPx) * ELLIPSE_RATIO
  });

  // Middle ellipse
  const middleEllipse = Ellipse({
    x,
    y,
    rx: INNER_RING_RADIUS_PX + (stickLengthPx / 2),
    ry: (INNER_RING_RADIUS_PX + (stickLengthPx / 2)) * ELLIPSE_RATIO
  });

  // Inner ellipse
  const innerEllipse = Ellipse({
    x,
    y,
    rx: INNER_RING_RADIUS_PX,
    ry: INNER_RING_RADIUS_PX * ELLIPSE_RATIO
  });

  return { innerEllipse, middleEllipse, outerEllipse };
};

export const DISCS_STICKS = STICK_LENGTHS_PX.map((stickLengthPx, i) => {
  const { innerEllipse, outerEllipse } = ELLIPSES(stickLengthPx, i);

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

export const DISCS_PETALS = STICK_LENGTHS_PX.map((stickLengthPx, i) => {
  const { innerEllipse, middleEllipse, outerEllipse } = ELLIPSES(stickLengthPx, i);

  const numLEDsInStrip = stickLengthPx * NUM_LEDS_PER_PX;

  const { leds, petals } = d3.range(NUM_PETALS_PER_DISC).reduce((acc, petalIndex) => {
    const r = radians(petalIndex * DEGREES_BETWEEN_PETALS);
    const r2 = radians(petalIndex * DEGREES_BETWEEN_PETALS + DEGREES_BETWEEN_PETALS / 2);
    const r3 = radians(petalIndex * DEGREES_BETWEEN_PETALS + DEGREES_BETWEEN_PETALS);
    const r4 = radians(petalIndex * DEGREES_BETWEEN_PETALS + DEGREES_BETWEEN_PETALS * 1.5);

    const p1 = pointOnEllipse(innerEllipse, r);
    const p2 = pointOnEllipse(middleEllipse, r);
    const p3 = pointOnEllipse(outerEllipse, r2);
    const p4 = pointOnEllipse(middleEllipse, r3);
    const p5 = pointOnLine(p3, p4, 0.5);
    const p6 = pointOnEllipse(outerEllipse, r3);
    const p7 = pointOnLine(p4, pointOnEllipse(outerEllipse, r4), 0.5);

    if (i == 0) {
      console.log('distance p1 p2', distance(p1, p2));
      console.log('distance p2 p3', distance(p2, p3));
      console.log('distance p3 p4', distance(p3, p4));
      console.log('distance p4 p5', distance(p4, p5));
      console.log('distance p5 p6', distance(p5, p6));
      console.log('distance p6 p7', distance(p6, p7));
    }

    const { strip1, strip2, strip3 } = d3
      .range(0, 1, 1 / numLEDsInStrip)
      .reduce((acc, howFar) => ({
        strip1: acc.strip1.concat(LED(pointOnLine(p1, p2, howFar))),
        strip2: acc.strip2.concat(LED(pointOnLine(p2, p3, howFar))),
        strip3: acc.strip3.concat(LED(pointOnLine(p4, p3, howFar)))
      }), { strip1: [], strip2: [], strip3: [] });

    const { strip4, strip5 } = d3
      .range(0, 1, 1 / numLEDsInStrip * 2)
      .reduce((acc, howFar) => ({
        strip4: acc.strip4.concat(LED(pointOnLine(p5, p6, howFar))),
        strip5: acc.strip5.concat(LED(pointOnLine(p7, p6, howFar))),
      }), { strip4: [], strip5: [] });

    acc.leds.push(strip1.concat(strip2).concat(strip3).concat(strip4).concat(strip5));
    acc.petals.inner1.push(strip1);
    acc.petals.inner2.push(strip2);
    acc.petals.inner2.push(strip3);
    acc.petals.outer.push(strip4);
    acc.petals.outer.push(strip5);

    return acc;
  }, { leds: [], petals: { inner1: [], inner2: [], outer: [] } });

  return { outerEllipse, innerEllipse, leds, petals };
});
