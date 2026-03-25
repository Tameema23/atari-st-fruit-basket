# Atari ST Fruit Basket

A fully functional double-buffered 2D arcade game built in **C and 68000 Assembly** for real Atari ST hardware. The player controls a basket to catch falling fruit while avoiding bombs. Difficulty scales dynamically over time.

Built as part of CPSC 233 at the University of Calgary.

---

## Gameplay

- Move the basket left and right to catch falling fruit
- Avoid bombs — collision ends the game
- Fruit and bomb spawn rates increase as time progresses
- Score is tracked and displayed in real-time
- Splash screen on launch, game over screen with final score on exit

---

## Technical Highlights

### Double Buffering
The game uses two framebuffers (front and back) swapped every tick of the Atari ST's 70Hz TOS clock. This eliminates screen tearing and produces smooth animation at the hardware level.

```c
Setscreen(backBuffer, frontBuffer, -1);  // swap buffers
```

### Custom Raster Graphics Engine
All drawing is done manually — no OS graphics calls. `RASTER.C` implements:
- Pixel plotting via direct memory write
- 16-bit and 32-bit bitmap blitting (`plot_bitmap_16`, `plot_bitmap_32`)
- Custom bitmap font rendering (`plot_text`)
- Full screen clear via word-level memory fill

### PSG Sound (Programmable Sound Generator)
Sound effects and music are driven by direct register writes to the YM2149 PSG chip at hardware addresses `0xFF8800` / `0xFF8802`:
- Fruit catch: chime effect via envelope + tone
- Bomb hit: noise channel explosion
- Game over: descending melody sequence
- Victory: ascending tone sequence

### Interrupt Service Routines (ISRs)
Keyboard input is handled without blocking using direct hardware polling. The system keyboard repeat flag is disabled at startup via privileged mode:

```c
old_ssp = Super(0);
*((char *)0x484) = 0;  // disable key repeat
Super(old_ssp);
```

### Dynamic Difficulty
Spawn rates for fruit and bombs are calculated from elapsed game time (TOS clock ticks / 70). Both spawn intervals and velocities increase as the session progresses, capped at minimum thresholds.

---

## Project Structure

```
├── main.c        # Game loop, double buffer swap, TOS clock timing
├── model.c       # Game state, collision detection, spawn logic
├── renderer.c    # Frame rendering, dirty-rect optimization
├── RASTER.C      # Low-level bitmap blitting, pixel ops, font rendering
├── input.c       # Keyboard polling
├── events.c      # Game event handling (catch, collision, game over)
├── psg.c         # PSG chip register read/write
├── music.c       # Background music sequencer
├── effects.c     # Sound effects (chime, explosion, melody)
├── font.c        # Bitmap font data and rendering
├── menu.c        # Splash screen
├── v_base.s      # 68000 Assembly — video base address setter
├── test.c        # Hardware test utilities
└── MAKEFILE      # Build system (cc68x cross-compiler)
```

---

## Building

You need the **cc68x** cross-compiler toolchain targeting the Motorola 68000.

```bash
make
```

This produces a `game` binary that runs natively on Atari ST hardware or a compatible emulator (e.g., Hatari).

---

## Authors

Tameem Aboueldahab, Andres Isturiz
