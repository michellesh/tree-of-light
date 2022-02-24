const defaults = {
  color: 'black',
  endAngle: 2 * Math.PI,
  radius: 1,
  startAngle: 0
};

export const LED = config => {
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
