export const getStrDiscRadii = discs =>
  discs
    .map(
      (disc, i) => `int16_t RADII_DISC_${i}[] = \{${disc.radii.join(', ')}\};`
    )
    .join('\n');

export const getStrDiscAngles = discs =>
  discs
    .map(
      (disc, i) => `int16_t ANGLES_DISC_${i}[] = \{${disc.angles.join(', ')}\};`
    )
    .join('\n');
