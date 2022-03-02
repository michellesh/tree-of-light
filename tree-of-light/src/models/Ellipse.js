import { radians } from 'utils';
import { BACKGROUND_COLOR } from 'const';

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
      context.strokeStyle = 'white';
      context.stroke();
      context.fillStyle = BACKGROUND_COLOR;
      context.fill();
    }
  });
};
