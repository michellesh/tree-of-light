import { clearCanvas } from 'utils';
import { showLEDs, showPetals } from 'animations';

export const petalRipple = (context, discs) => {
  clearCanvas(context);

  const discStates = discs.map(d => ({
    petalType: 'inner1',
    prevIndex: 0,
    index: 1
  }));

  const _petalRipple = () => {
    discs.forEach((disc, d) => {
      const { index, prevIndex, petalType } = discStates[d];
      disc.petals[petalType].forEach(ledStrip => {
        if (index < ledStrip.length) {
          ledStrip[index] = ledStrip[index].on();
        }
        if (prevIndex < ledStrip.length) {
          ledStrip[prevIndex] = ledStrip[prevIndex].off();
        }
      });
    });
    discStates.forEach((state, d) => {
      state.prevIndex = state.index;
      state.index++;
      if (state.index > discs[d].petals[state.petalType][0].length) {
        state.index = 0;
        state.petalType =
          state.petalType == 'inner1'
            ? 'inner2'
            : state.petalType == 'inner2'
            ? 'outer'
            : 'inner1';
      }
    });
    showPetals(context, discs);
    window.reqId = window.requestAnimationFrame(_petalRipple);
  };

  window.reqId = window.requestAnimationFrame(_petalRipple);
};

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
