import { clearCanvas } from 'utils';
import { showLEDs } from 'animations';

export const explode = (context, DISCS) => {
  clearCanvas(context);

  const maxStrandLength = DISCS.reduce(
    (acc, disc) => (disc.leds[0].length > acc ? disc.leds[0].length : acc),
    0
  );
  let ledIndex = 0;

  const _explode = () => {
    DISCS.forEach(disc => {
      disc.leds.forEach(ledStrip => {
        if (ledIndex < ledStrip.length) {
          ledStrip[ledIndex] = ledStrip[ledIndex].radius(3);
        }
        if (ledIndex > 0 && ledIndex - 1 < ledStrip.length) {
          ledStrip[ledIndex - 1] = ledStrip[ledIndex - 1].radius(1);
        }
      });
    });
    showLEDs(context, DISCS);
    ledIndex = ledIndex === maxStrandLength ? 0 : ledIndex + 1;
    window.requestAnimationFrame(_explode);
  };

  window.requestAnimationFrame(_explode);
};
