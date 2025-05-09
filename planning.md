# Ant Mover
A "maze solver", basically a `Vec2` point that tries to move up, right, down or left every move adding it's position to a stack.

The point will not walk onto positions it has been on before, labelling these as "illegal directions". 
If there is no legal direction it retraces it's steps until there is a valid direction through a stack.

After every move, the new position gets a random color as `Vec4` based on the previous tiles color.

## Project data
- Vec4 array with the size `IMAGE_WIDTH` * `IMAGE_HEIGHT` initialized to "transparent color"
- Vec2 as an index to the array (the ants position)
- `StackVec2` for the used positions

## Flow
- Make a selection of legal moves from the `Vec4` color array in the four directions around position (where legal is black transparent) and randomize between them to change the position.
- If there is a legal position, randomize the color value to set the `Vec4` color arrays value at position as index.
- If no legal moves exist, pop the stack until there are legal moves.
- Exit the program when no legal moves exists.

## Needed tools
- [X] `GameState`
- [X] `Vec2`
- [X] `Vec4`
- [X] `Vec4` to `SDL_Color` (vec4_to_color)
- [X] `StackVec2`
- [X] Random helper
- [X] Math helper

### GameState
A struct that holds all perpetual information.

### Vec2
Normal Vector2 with x and y floats.

### Vec4
Vector4 with r, g, b and a floats to function like a color.

### Vec4 to SDL_Color
Converts the Vec4 four floats (0 to 1) to SDL_Color (0 to 255)

### StackVec2
A struct with a Vec2 array and a top index that is handled by stack_vec2.h.

### Random Helper
Provides two functions, one for a random float between two values and one for uniform randomness between two values.

### Math Helper
Just adds min/max and clamp for integers and floats.