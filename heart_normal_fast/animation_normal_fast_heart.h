int animationFrames = 8;

int animationDelays[] = { 500, 200, 500, 200, 100, 100, 100, 100 };

// Animation is designed for 8x8 pixels
uint8_t animation[][16] = {
  { 0x0, 0x0, 0x30, 0xc, 0xcc, 0x33, 0xc, 0x30, 0x30, 0xc, 0xc0, 0x3, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x30, 0xc, 0xcc, 0x33, 0x3, 0xc0, 0x3, 0xc0, 0xc, 0x30, 0x30, 0xc, 0xc0, 0x3, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x3c, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xf0, 0xf, 0xc0, 0x3, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x3c, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xf0, 0xf, 0xc0, 0x3, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};
