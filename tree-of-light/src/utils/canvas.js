export const clearCanvas = context => {
  const { width, height } = getCanvasDimensions(context);
  context.clearRect(0, 0, width, height);
};

export const getCanvasDimensions = context => {
  if (context) {
    const { width, height } = context.canvas.getBoundingClientRect();
    return { width, height };
  }
};
