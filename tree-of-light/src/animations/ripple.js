import { clearCanvas } from 'utils';
import { showLEDs } from 'animations';

export const ripple = (context, discs) => {
  clearCanvas(context);

  const maxStrandLength = discs.reduce(
    (acc, disc) => (disc.leds[0].length > acc ? disc.leds[0].length : acc),
    0
  );
  let ledIndex = 0;

  const _ripple = () => {
    discs.forEach(disc => {
      disc.leds.forEach(ledStrip => {
        if (ledIndex < ledStrip.length) {
          ledStrip[ledIndex] = ledStrip[ledIndex].on();
        }
        if (ledIndex > 0 && ledIndex - 1 < ledStrip.length) {
          ledStrip[ledIndex - 1] = ledStrip[ledIndex - 1].off();
        }
      });
    });
    showLEDs(context, discs);
    ledIndex = ledIndex === maxStrandLength ? 0 : ledIndex + 1;
    window.reqId = window.requestAnimationFrame(_ripple);
  };

  window.reqId = window.requestAnimationFrame(_ripple);
};
