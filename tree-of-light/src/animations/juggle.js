import { clearCanvas } from 'utils';
import { showLEDs } from 'animations';

export const juggle = (context, DISCS) => {
  clearCanvas(context);

  let discStates = DISCS.map(d => ({
    prevIndex: 0,
    index: 1,
    outward: true,
    length: d.leds[0].length
  }));

  const _juggle = () => {
    DISCS.forEach((disc, i) => {
      const state = discStates[i];
      disc.leds.forEach(ledStrip => {
        ledStrip[state.index] = ledStrip[state.index].on();
        ledStrip[state.prevIndex] = ledStrip[state.prevIndex].off();
      });
    });
    discStates.forEach(state => {
      state.prevIndex = state.index;
      if (state.outward) {
        state.index++;
        if (state.index >= state.length) {
          state.outward = false;
          state.index = state.length - 2;
        }
      } else {
        state.index--;
        if (state.index < 0) {
          state.outward = true;
          state.index = 1;
        }
      }
    });
    showLEDs(context, DISCS);
    window.requestAnimationFrame(_juggle);
  };

  window.requestAnimationFrame(_juggle);
};
