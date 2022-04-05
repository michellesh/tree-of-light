import * as d3 from 'd3';

import { WIDTH } from 'const';
import { Ellipse } from 'models/Ellipse';
import { LED } from 'models/LED';
import {
  angleBetweenCircumferencePts,
  degrees,
  distance,
  pointOnEllipse,
  pointOnLine,
  radians
} from 'utils';

//const ELLIPSE_RATIO = 0.5; // ratio of width/height for each ellipse
const ELLIPSE_RATIO = 1;
const ELLIPSE_MAX_WIDTH = 300; // width of widest ellipse on top in px
const DISTANCE_BETWEEN_DISCS = 100; // space between each disc in px
const NUM_PETALS_PER_DISC = 6;
const DEGREES_BETWEEN_PETALS = 360 / NUM_PETALS_PER_DISC;
const TOP_OFFSET = 160; // number of pixels offset from top of canvas

// Radii of discs are as follows (in ft).
// They should all start at the edge of a 24" diameter circle
// (meaning the lowest layer is 8' total diameter: 3+2+3).
const DISC_RADII_FT = [12, 10.875, 9.75, 8.625, 7.5, 6.375, 5.25, 4.125, 3];
const INNER_RING_RADIUS_FT = 1;

const petalLengths = {
  0: { p1: 8, p2: 10, p3: 6 },
  1: { p1: 8, p2: 9, p3: 5 },
  2: { p1: 7, p2: 7, p3: 5 },
  3: { p1: 6, p2: 7, p3: 4 },
  4: { p1: 5, p2: 6, p3: 4 },
  5: { p1: 4, p2: 5, p3: 3 },
  6: { p1: 3, p2: 4, p3: 2 },
  7: { p1: 2, p2: 3, p3: 2 },
  8: { p1: 1, p2: 2, p3: 1 }
};

// the offset of the start of the very first petal group
// compared to the top disc
const addDegreeOffset = {
  0: 0,
  1: 60,
  2: 120,
  3: 300,
  4: 300,
  5: 0,
  6: 60,
  7: 120,
  8: 120
};

const ftToPx = d3
  .scaleLinear()
  .domain([0, d3.max(DISC_RADII_FT)])
  .range([0, ELLIPSE_MAX_WIDTH]);

const DISC_RADII_PX = DISC_RADII_FT.map(ftToPx);
const INNER_RING_RADIUS_PX = ftToPx(INNER_RING_RADIUS_FT);

const scaleRadius = d3
  .scaleLinear()
  .domain([0, ELLIPSE_MAX_WIDTH + INNER_RING_RADIUS_PX])
  .range([0, 255]);

const Disc = (discRadius, discIndex) => {
  const { innerEllipse, middleEllipse, outerEllipse } = getEllipses(
    discRadius,
    discIndex
  );

  const petals = d3
    .range(NUM_PETALS_PER_DISC)
    .map(petalIndex =>
      getPetalStrips(
        discIndex,
        petalIndex,
        innerEllipse,
        middleEllipse,
        outerEllipse
      )
    );

  const allLeds = petals.flatMap(strips => strips.flatMap(strip => strip));

  return {
    radius: discRadius,
    outerEllipse,
    innerEllipse,
    allLeds,
    leds: petals.map(strips => strips.flatMap(strip => strip)),
    petals: {
      inner1: petals.map(strips => strips[0]),
      inner2: petals.reduce(
        (acc, strips) => acc.concat([strips[1]], [strips[2].reverse()]),
        []
      ),
      outer: petals.reduce(
        (acc, strips) => acc.concat([strips[3]], [strips[4].reverse()]),
        []
      )
    },
    radii: allLeds.map(led => getRadius(led, outerEllipse)),
    angles: allLeds.map(led => getAngle(led, discIndex, outerEllipse))
  };
};

// Generate the ellipses for a disc
//   inner: the hole in the center of the disc
//   outer: the circumference of the disc
//   middle: halfway between, where the inner petal are at widest point
const getEllipses = (discRadius, discIndex) => {
  // Center point of disc
  const x = WIDTH / 2;
  const y = TOP_OFFSET + DISTANCE_BETWEEN_DISCS * discIndex;
  return {
    innerEllipse: Ellipse({
      x,
      y,
      rx: INNER_RING_RADIUS_PX,
      ry: INNER_RING_RADIUS_PX * ELLIPSE_RATIO
    }),
    outerEllipse: Ellipse({
      x,
      y,
      rx: INNER_RING_RADIUS_PX + discRadius,
      ry: (INNER_RING_RADIUS_PX + discRadius) * ELLIPSE_RATIO
    }),
    middleEllipse: Ellipse({
      x,
      y,
      rx: INNER_RING_RADIUS_PX + discRadius / 2,
      ry: (INNER_RING_RADIUS_PX + discRadius / 2) * ELLIPSE_RATIO
    })
  };
};

// Get XY coords for all the intersections in one petal group on a disc
const getPetalCorners = (
  innerEllipse,
  middleEllipse,
  outerEllipse,
  petalIndex
) => {
  const r = radians(petalIndex * DEGREES_BETWEEN_PETALS);
  const r2 = radians(
    petalIndex * DEGREES_BETWEEN_PETALS + DEGREES_BETWEEN_PETALS / 2
  );
  const r3 = radians(
    petalIndex * DEGREES_BETWEEN_PETALS + DEGREES_BETWEEN_PETALS
  );
  const r4 = radians(
    petalIndex * DEGREES_BETWEEN_PETALS + DEGREES_BETWEEN_PETALS * 1.5
  );

  const p1 = pointOnEllipse(innerEllipse, r);
  const p2 = pointOnEllipse(middleEllipse, r);
  const p3 = pointOnEllipse(outerEllipse, r2);
  const p4 = pointOnEllipse(middleEllipse, r3);
  const p5 = pointOnLine(p3, p4, 0.5);
  const p6 = pointOnEllipse(outerEllipse, r3);
  const p7 = pointOnLine(p4, pointOnEllipse(outerEllipse, r4), 0.5);

  return { p1, p2, p3, p4, p5, p6, p7 };
};

// Generate all LEDs for one petal group on a disc.
// Returns an array of 5 strips, where each strip is an array of LEDs.
const getPetalStrips = (
  discIndex,
  petalIndex,
  innerEllipse,
  middleEllipse,
  outerEllipse
) => {
  const { p1, p2, p3, p4, p5, p6, p7 } = getPetalCorners(
    innerEllipse,
    middleEllipse,
    outerEllipse,
    petalIndex
  );

  const step1 = 1 / petalLengths[discIndex].p1;
  const step2 = 1 / petalLengths[discIndex].p2;
  const step3 = 1 / petalLengths[discIndex].p3;

  const strip1 = d3
    .range(step1 / 2, 1, step1)
    .reduce(
      (acc, howFar) =>
        acc.concat(LED(pointOnLine(p1, p2, howFar)).color('yellow')),
      []
    );

  const { strip2, strip3 } = d3.range(step2 / 2, 1, step2).reduce(
    (acc, howFar) => ({
      strip2: acc.strip2.concat(
        LED(pointOnLine(p2, p3, howFar)).color('green')
      ),
      strip3: acc.strip3.concat(LED(pointOnLine(p3, p4, howFar)).color('green'))
    }),
    { strip2: [], strip3: [] }
  );

  const { strip4, strip5 } = d3.range(step3 / 2, 1, step3).reduce(
    (acc, howFar) => ({
      strip4: acc.strip4.concat(LED(pointOnLine(p7, p6, howFar)).color('blue')),
      strip5: acc.strip5.concat(LED(pointOnLine(p6, p5, howFar)).color('blue'))
    }),
    { strip4: [], strip5: [] }
  );

  return [strip1, strip2, strip3, strip4, strip5];
};

// Given an LED for a Disc, get how far that LED is from the origin
const getRadius = (led, outerEllipse) => {
  const radius = outerEllipse.rx;
  const scaledRadius = scaleRadius(radius);
  const pxToRadius = d3
    .scaleLinear()
    .domain([0, radius])
    .range([0, scaledRadius]);
  return Math.round(pxToRadius(distance(led, outerEllipse)));
};

// Given an LED for a Disc, get how far around the disc that LED is
const getAngle = (led, discIndex, outerEllipse) => {
  let d, ellipsePt;
  if (led.x < outerEllipse.x) {
    ellipsePt = pointOnEllipse(outerEllipse, radians(180));
    d = angleBetweenCircumferencePts(outerEllipse, ellipsePt, led);
    d = degrees(d) + 180;
  } else {
    ellipsePt = pointOnEllipse(outerEllipse, radians(0));
    d = angleBetweenCircumferencePts(outerEllipse, ellipsePt, led);
    d = degrees(d);
  }
  d = Math.round(d) - addDegreeOffset[discIndex];
  return d < 0 ? d + 360 : d;
};

export const DISCS = DISC_RADII_PX.map(Disc);
