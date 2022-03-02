import * as d3 from 'd3';

import { WIDTH } from 'const';
import { Ellipse } from 'models/Ellipse';
import { LED } from 'models/LED';
import { pointOnEllipse, pointOnLine, radians } from 'utils';

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

const ELLIPSES = (stickLengthPx, index) => {
  // Center point of disc
  const x = WIDTH / 2;
  const y = TOP_OFFSET + DISTANCE_BETWEEN_DISCS * index;

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

  return { innerEllipse, outerEllipse };
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
