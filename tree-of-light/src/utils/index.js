const OFFSET = Math.PI / 2;

export const angleBetween = (p1, p2) =>
  Math.atan2(p2.y - p1.y, p2.x - p1.x) - OFFSET;

export const distance = (p1, p2) =>
  Math.sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

//export const angleBetweenCircumferencePts = (p1, p2, r) =>
//  Math.acos((2 * r * r - (Math.pow(distance(p1, p2), 2))) / (2 * r * r));

// p1 is origin of circle
export const angleBetweenCircumferencePts = (p1, p2, p3) => {
  const p12 = distance(p1, p2);
  const p13 = distance(p1, p3);
  const p23 = distance(p2, p3);
  return Math.acos(
    ((p12 * p12) + (p13 * p13) - (p23 * p23)) /
    (2 * p12 * p13)
  );
};

export const degrees = radians => (180 * (radians)) / Math.PI;

export const radians = degrees => (degrees * Math.PI) / 180 - OFFSET;

// get a point along the line that forms between p1 and p2
// howFar value between 0 and 1, how far along that line
export const pointOnLine = (p1, p2, howFar) => ({
  x: p1.x + (p2.x - p1.x) * howFar,
  y: p1.y + (p2.y - p1.y) * howFar
});

export const pointOnEllipse = (ellipse, angleRadians) => ({
  x:
    ellipse.x +
    ellipse.rx * Math.cos(angleRadians) * Math.cos(ellipse.rotation) -
    ellipse.ry * Math.sin(angleRadians) * Math.sin(ellipse.rotation),
  y:
    ellipse.y +
    ellipse.rx * Math.cos(angleRadians) * Math.sin(ellipse.rotation) +
    ellipse.ry * Math.sin(angleRadians) * Math.cos(ellipse.rotation)
});

export * from './canvas';
export * from './log';
