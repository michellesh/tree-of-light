import { radians } from 'utils';

const defaults = {
  rotation: 0,
  startAngle: radians(0),
  endAngle: radians(360)
};

export const Ellipse = config => {
  const _ellipse = { ...defaults, ...config };
  return Object.freeze({
    ..._ellipse,
    draw: context => {
      const { x, y, rx, ry, rotation, startAngle, endAngle } = _ellipse;
      context.beginPath();
      context.ellipse(x, y, rx, ry, rotation, startAngle, endAngle);
      context.strokeStyle = 'black';
      context.stroke();
    }
  });
};
