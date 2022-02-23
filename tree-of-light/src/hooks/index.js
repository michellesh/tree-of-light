import { useEffect, useRef, useState } from 'react';

export const useCanvas = () => {
  const canvasRef = useRef(null);
  const [context, setContext] = useState();

  useEffect(() => {
    const node = canvasRef.current;
    if (node) {
      setContext(node.getContext('2d'));
    }
  }, [canvasRef]);

  return [canvasRef, context];
};
