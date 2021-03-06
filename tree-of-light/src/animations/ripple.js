import { clearCanvas } from 'utils';
import { showAllLEDs, showLEDs, showPetals } from 'animations';

export const radiusRipple = (context, discs) => {
  clearCanvas(context);

  let radius = 0;
  const threshold = 10;

  const _radiusRipple = () => {
    discs.forEach((disc, d) => {
      disc.allLeds = disc.allLeds.map((led, i) =>
        Math.abs(disc.radii[i] - radius) < threshold ? led.on() : led.off()
      );
    });

    showAllLEDs(context, discs);
    radius++;
    if (radius >= 255) {
      radius = 0;
    }
    window.reqId = window.requestAnimationFrame(_radiusRipple);
  };

  window.reqId = window.requestAnimationFrame(_radiusRipple);
};

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
  };

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
    if (
      discStates[0].inner2.index > discStates[0].inner2.length &&
      discStates[0].outer.index > discStates[0].outer.length
    ) {
      discStates.forEach((state, d) => resetDiscState(d));
    } else {
      discStates.forEach(state => {
        if (state.inner1.index <= state.inner1.length) {
          incIndex(state.inner1);
        }
        if (state.inner1.index > state.inner1.length) {
          incIndex(state.inner2);
        }
        if (state.inner2.index > state.inner2.length / 2) {
          incIndex(state.outer);
        }
      });
    }
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
