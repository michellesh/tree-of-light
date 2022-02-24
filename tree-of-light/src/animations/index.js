import { clearCanvas } from 'utils';

export const showLEDs = (context, DISCS) => {
  clearCanvas(context);
  DISCS.forEach(disc => {
    disc.outerEllipse.draw(context);
    disc.innerEllipse.draw(context);
    disc.leds.forEach(ledStrip =>
      ledStrip.forEach(led => led.draw(context))
    );
  })
};

export * from './explode';
