import { clearCanvas } from 'utils';
import { showLEDs, showPetals } from 'animations';

export const petalRipple = (context, discs) => {
  clearCanvas(context);

  const discStates = discs.map(d => ({
    inner1: { prevIndex: -2, index: -1, length: d.petals.inner1[0].length },
    inner2: { prevIndex: -2, index: -1, length: d.petals.inner2[0].length },
    outer: { prevIndex: -2, index: -1, length: d.petals.outer[0].length }
  }));
  const resetDiscState = discIndex => {
    discStates[discIndex].inner1.prevIndex = -2;
    discStates[discIndex].inner1.index = -1;
    discStates[discIndex].inner2.prevIndex = -2;
    discStates[discIndex].inner2.index = -1;
    discStates[discIndex].outer.prevIndex = -2;
    discStates[discIndex].outer.index = -1;
  };
  const incIndex = discState => {
    discState.prevIndex = discState.index;
    discState.index++;
  }

  const _petalRipple = () => {
    discs.forEach((disc, d) => {
      ['inner1', 'inner2', 'outer'].forEach(petalType => {
        const { index, prevIndex } = discStates[d][petalType];
        disc.petals[petalType].forEach(ledStrip => {
          if (index >= 0 && index < ledStrip.length) {
            ledStrip[index] = ledStrip[index].on();
          }
          if (prevIndex >= 0 && prevIndex < ledStrip.length) {
            ledStrip[prevIndex] = ledStrip[prevIndex].off();
          }
        });
      });
    });
    discStates.forEach((state, d) => {
      if (state.inner1.index <= state.inner1.length) {
        incIndex(state.inner1);
      }
      if (state.inner1.index > state.inner1.length) {
        incIndex(state.inner2);
      }
      if (state.inner2.index > state.inner2.length / 2) {
        incIndex(state.outer);
      }
      if (
        state.inner2.index > state.inner2.length &&
        state.outer.index > state.outer.length
      ) {
        resetDiscState(d);
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
