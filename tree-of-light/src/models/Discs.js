import * as d3 from 'd3';

import { WIDTH } from 'const';
import { Ellipse } from 'models/Ellipse';
import { LED } from 'models/LED';
import { angleBetweenCircumferencePts, degrees, distance, pointOnEllipse, pointOnLine, radians } from 'utils';

//const ELLIPSE_RATIO = 0.5; // ratio of width/height for each ellipse
const ELLIPSE_RATIO = 1;
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
  8: 120,
}

const ftToPx = d3
  .scaleLinear()
  .domain([0, d3.max(STICK_LENGTHS_FT)])
  .range([0, ELLIPSE_MAX_WIDTH]);

const STICK_LENGTHS_PX = STICK_LENGTHS_FT.map(ftToPx);
const NUM_LEDS_PER_PX = NUM_LEDS_PER_FT / ftToPx(1);
const INNER_RING_RADIUS_PX = ftToPx(INNER_RING_RADIUS_FT);
console.log('INNER_RING_RADIUS_PX',INNER_RING_RADIUS_PX);

const scaleRadius = d3
  .scaleLinear()
  .domain([0, ELLIPSE_MAX_WIDTH + INNER_RING_RADIUS_PX])
  .range([0, 255]);

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
    rx: INNER_RING_RADIUS_PX + stickLengthPx / 2,
    ry: (INNER_RING_RADIUS_PX + stickLengthPx / 2) * ELLIPSE_RATIO
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
  const { innerEllipse, middleEllipse, outerEllipse } = ELLIPSES(
    stickLengthPx,
    i
  );

  const numLEDsInStrip = stickLengthPx * NUM_LEDS_PER_PX;

  const { allLeds, leds, petals } = d3.range(NUM_PETALS_PER_DISC).reduce(
    (acc, petalIndex) => {
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

      const step1 = 1 / petalLengths[i].p1;
      const step2 = 1 / petalLengths[i].p2;
      const step3 = 1 / petalLengths[i].p3;

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
          strip3: acc.strip3.concat(
            LED(pointOnLine(p3, p4, howFar)).color('green')
          )
        }),
        { strip2: [], strip3: [] }
      );

      const { strip4, strip5 } = d3.range(step3 / 2, 1, step3).reduce(
        (acc, howFar) => ({
          strip4: acc.strip4.concat(
            LED(pointOnLine(p7, p6, howFar)).color('blue')
          ),
          strip5: acc.strip5.concat(
            LED(pointOnLine(p6, p5, howFar)).color('blue')
          )
        }),
        { strip4: [], strip5: [] }
      );

      const petalGroup = strip1
        .concat(strip2)
        .concat(strip3)
        .concat(strip4)
        .concat(strip5);
      acc.allLeds = acc.allLeds.concat(petalGroup);
      acc.leds.push(petalGroup);
      acc.petals.inner1.push(strip1);
      acc.petals.inner2.push(strip2);
      acc.petals.inner2.push(strip3.reverse());
      acc.petals.outer.push(strip4);
      acc.petals.outer.push(strip5.reverse());

      return acc;
    },
    { allLeds: [], leds: [], petals: { inner1: [], inner2: [], outer: [] } }
  );

  const radius = outerEllipse.rx;
  const scaledRadius = scaleRadius(radius);
  const pxToRadius = d3
    .scaleLinear()
    .domain([0, radius])
    .range([0, scaledRadius]);
  const radii = allLeds.map(led =>
    Math.round(pxToRadius(distance(led, outerEllipse)))
  );

  //const ellipsePt = allLeds[0];
  const degreeOffset = addDegreeOffset[i];
  const ellipsePt = pointOnEllipse(outerEllipse, radians(0));
  const ellipsePt180 = pointOnEllipse(outerEllipse, radians(180));
  const angles = allLeds.map(led => {
    let d;
    if (led.x < outerEllipse.x) {
      d = angleBetweenCircumferencePts(outerEllipse, ellipsePt180, led);
      d = degrees(d) + 180;
    } else {
      d = angleBetweenCircumferencePts(outerEllipse, ellipsePt, led);
      d = degrees(d);
    }
    d = Math.round(d) - degreeOffset;
    return d < 0 ? d + 360 : d;
  });

  return { outerEllipse, innerEllipse, allLeds, leds, petals, radii, angles };
});
