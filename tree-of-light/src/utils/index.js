const OFFSET = Math.PI / 2;

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
