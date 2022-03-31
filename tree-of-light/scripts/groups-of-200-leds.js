/*
 * This script calculates divides LEDs into groups of 200
 * and outputs a markdown table with the results
 */

const MAX_LEDS = 200;
const MAX_LEDS_PIN_4 = 202; // I messed up on this pin and ended up with 2 extra LEDs
const LEDS_IN_PETAL_GROUP_PER_DISC = [40, 36, 31, 28, 25, 20, 15, 12, 7];

const sum = arr =>
  arr.reduce((acc, x) => acc + LEDS_IN_PETAL_GROUP_PER_DISC[x], 0);

const distributeLEDs = () => {
  const pins = {};
  let petalCount = 0;
  let discIndex = 0;
  let dataPin = 1;
  while (discIndex < 9) {
    if (!pins[dataPin]) {
      pins[dataPin] = [];
    }

    const ledsSoFar =
      sum(pins[dataPin]) + LEDS_IN_PETAL_GROUP_PER_DISC[discIndex];
    if (
      ledsSoFar <= MAX_LEDS ||
      (dataPin == 4 && ledsSoFar <= MAX_LEDS_PIN_4)
    ) {
      pins[dataPin].push(discIndex);
      petalCount++;
      if (petalCount == 6) {
        discIndex++;
        petalCount = 0;
      }
    } else {
      dataPin++;
    }
  }
  return pins;
};

const getNumGroupsByDisc = discIndexArr =>
  discIndexArr.reduce((acc, discIndex) => {
    acc[discIndex] = acc[discIndex] ? acc[discIndex] + 1 : 1;
    return acc;
  }, {});

const getStr = (discIndex, numGroups) =>
  `Disc ${discIndex}: ${Array(numGroups)
    .fill(LEDS_IN_PETAL_GROUP_PER_DISC[discIndex])
    .join(', ')}`;

const printTable = pins => {
  const totalPins = Math.max(...Object.keys(pins).map(Number));
  const totalLEDs = Object.values(pins).reduce((acc, p) => acc + sum(p), 0);
  Object.keys(pins).forEach(pin => {
    const numGroupsByDisc = getNumGroupsByDisc(pins[pin]);
    const numLEDsPerDisc = Object.keys(numGroupsByDisc)
      .map(discIndex => getStr(discIndex, numGroupsByDisc[discIndex]))
      .join('<br />');

    const numWiresLeft =
      Number(pin) < Object.keys(pins).length
        ? totalPins - pins[Number(pin) + 1][0]
        : 0;

    console.log(
      `| ${[
        pin,
        numLEDsPerDisc,
        `${sum(pins[pin])} LEDs`,
        `${numWiresLeft} wires`
      ].join(' | ')} |`
    );
  });

  console.log('Total LEDs:', totalLEDs);
};

const pins = distributeLEDs();
printTable(pins);
