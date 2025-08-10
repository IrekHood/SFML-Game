#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <unordered_set>
#include <queue>

#define WIDTH 25
#define HEIGHT 20
#define TILE_SIZE 8
#define SCALE 7
#define MINES 120

enum TileType
{
    TILE_COVER,
    TILE_EMPTY,
    TILE_FLAG,
    TILE_ONE,
    TILE_TWO,
    TILE_THREE,
    TILE_FOUR,
    TILE_FIVE,
    TILE_SIX,
    TILE_SEVEN,
    TILE_EIGHT,
    TILE_MINE
};

void drawTile(sf::RenderWindow &window, int x, int y, sf::Sprite sprt)
{
    // Set the position of the sprite based on the tile coordinates
    sprt.setPosition(sf::Vector2f{(float)(x * TILE_SIZE * SCALE), (float)(y * TILE_SIZE * SCALE)});
    // Draw the sprite to the window
    window.draw(sprt);
}

std::unordered_set<std::array<int, 2>> bfs(int x, int y, int mine_grid[WIDTH][HEIGHT]){
    std::unordered_set<std::tuple<int, int>> w{std::tuple{x, y}};
}
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WIDTH * TILE_SIZE * SCALE, HEIGHT * TILE_SIZE * SCALE}), "miny");
    window.setFramerateLimit(60);

    // random

    srand(time(nullptr)); // Seed the random number generator

    // load resources
    sf::Texture tile("assets/tile.png");
    sf::Texture empty("assets/empty.png");
    sf::Texture flag("assets/flag.png");
    sf::Texture one("assets/1.png");
    sf::Texture two("assets/2.png");
    sf::Texture three("assets/3.png");
    sf::Texture four("assets/4.png");
    sf::Texture five("assets/5.png");
    sf::Texture six("assets/6.png");
    sf::Texture seven("assets/7.png");
    sf::Texture eight("assets/8.png");
    sf::Texture mine("assets/mine.png");

    if (!tile.loadFromFile("assets/tile.png") ||
        !empty.loadFromFile("assets/empty.png") ||
        !flag.loadFromFile("assets/flag.png") ||
        !one.loadFromFile("assets/1.png") ||
        !two.loadFromFile("assets/2.png") ||
        !three.loadFromFile("assets/3.png") ||
        !four.loadFromFile("assets/4.png") ||
        !five.loadFromFile("assets/5.png") ||
        !six.loadFromFile("assets/6.png") ||
        !seven.loadFromFile("assets/7.png") ||
        !eight.loadFromFile("assets/8.png") ||
        !mine.loadFromFile("assets/mine.png"))
    {
        return -1; // Exit if any texture fails to load
    }

    // make sprites
    sf::Sprite tileSprite(tile);
    sf::Sprite emptySprite(empty);
    sf::Sprite flagSprite(flag);
    sf::Sprite oneSprite(one);
    sf::Sprite twoSprite(two);
    sf::Sprite threeSprite(three);
    sf::Sprite fourSprite(four);
    sf::Sprite fiveSprite(five);
    sf::Sprite sixSprite(six);
    sf::Sprite sevenSprite(seven);
    sf::Sprite eightSprite(eight);
    sf::Sprite mineSprite(mine);

    // Set the scale for the sprites
    tileSprite.setScale(sf::Vector2f(SCALE, SCALE));
    emptySprite.setScale(sf::Vector2f(SCALE, SCALE));
    flagSprite.setScale(sf::Vector2f(SCALE, SCALE));
    oneSprite.setScale(sf::Vector2f(SCALE, SCALE));
    twoSprite.setScale(sf::Vector2f(SCALE, SCALE));
    threeSprite.setScale(sf::Vector2f(SCALE, SCALE));
    fourSprite.setScale(sf::Vector2f(SCALE, SCALE));
    fiveSprite.setScale(sf::Vector2f(SCALE, SCALE));
    sixSprite.setScale(sf::Vector2f(SCALE, SCALE));
    sevenSprite.setScale(sf::Vector2f(SCALE, SCALE));
    eightSprite.setScale(sf::Vector2f(SCALE, SCALE));
    mineSprite.setScale(sf::Vector2f(SCALE, SCALE));

    // create a grid of tiles
    int draw_grid[WIDTH][HEIGHT];
    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            draw_grid[x][y] = TILE_COVER; // Initialize all tiles as empty
        }
    }

    // create mine grid
    int mine_grid[WIDTH][HEIGHT];
    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            mine_grid[x][y] = TILE_COVER; // Initialize all tiles as empty
        }
    }
    int mines = MINES;
    while (mines)
    {
        if (mine_grid[rand() % WIDTH][rand() % HEIGHT] != TILE_MINE)
        {
            mine_grid[rand() % WIDTH][rand() % HEIGHT] = TILE_MINE; // Place a mine
            --mines;                                                // Decrease the number of mines left to place
        }
    }
    // calculate numbers around mines
    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            if (mine_grid[x][y] == TILE_MINE)
                continue; // Skip if it's a mine

            int mine_count = 0;
            // Check all adjacent tiles
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    if (dx == 0 && dy == 0)
                        continue; // Skip the tile itself
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && mine_grid[nx][ny] == TILE_MINE)
                    {
                        ++mine_count; // Count adjacent mines
                    }
                }
            }

            // Set the tile type based on the mine count
            switch (mine_count)
            {
            case 0:
                mine_grid[x][y] = TILE_EMPTY;
                break;
            case 1:
                mine_grid[x][y] = TILE_ONE;
                break;
            case 2:
                mine_grid[x][y] = TILE_TWO;
                break;
            case 3:
                mine_grid[x][y] = TILE_THREE;
                break;
            case 4:
                mine_grid[x][y] = TILE_FOUR;
                break;
            case 5:
                mine_grid[x][y] = TILE_FIVE;
                break;
            case 6:
                mine_grid[x][y] = TILE_SIX;
                break;
            case 7:
                mine_grid[x][y] = TILE_SEVEN;
                break;
            case 8:
                mine_grid[x][y] = TILE_EIGHT;
                break;
            }
        }
    }

    // settup variables
    int pos[2];
    pos[0] = 0;
    pos[1] = 0;

    sf::RectangleShape rect(sf::Vector2f{TILE_SIZE * SCALE, TILE_SIZE * SCALE});
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(255, 255, 255));
    rect.setOutlineThickness(SCALE);

    // Main loop

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close(); // Close the window if Escape is pressed
            }
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::W || keyPressed->scancode == sf::Keyboard::Scan::Up) {
                    if ((pos[1] - 1) >= 0) {
                        pos[1]--;
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::S || keyPressed->scancode == sf::Keyboard::Scan::Down) {
                    if ((pos[1] + 1) < HEIGHT) {
                        pos[1]++;
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::A || keyPressed->scancode == sf::Keyboard::Scan::Left) {
                    if ((pos[0] - 1) >= 0) {
                        pos[0]--;
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::D || keyPressed->scancode == sf::Keyboard::Scan::Right) {
                    if ((pos[0] + 1) < WIDTH) {
                        pos[0]++;
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::Space || keyPressed->scancode == sf::Keyboard::Scan::G) {
                    if (draw_grid[pos[0]][pos[1]] != TILE_FLAG)
                    {
                        // If the tile is not flagged, reveal it
                        draw_grid[pos[0]][pos[1]] = TILE_EMPTY;
                    }
                }         
                if (keyPressed->scancode == sf::Keyboard::Scan::B || keyPressed->scancode == sf::Keyboard::Scan::F) {
                    if (draw_grid[pos[0]][pos[1]] == TILE_FLAG)
                    {
                        // If the tile is already flagged, remove the flag
                        draw_grid[pos[0]][pos[1]] = TILE_COVER;
                    }
                    else if (draw_grid[pos[0]][pos[1]] == TILE_COVER)
                    {
                        // Only place a flag if the tile is covered
                        draw_grid[pos[0]][pos[1]] = TILE_FLAG;
                    }
                }          

            }

            //flag the tile that is pressed
            if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right)
                {
                    sf::Vector2i mousePos{sf::Mouse::getPosition(window)};
                    if (draw_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] == TILE_FLAG)
                    {
                        // If the tile is already flagged, remove the flag
                        draw_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] = TILE_COVER;
                    }
                    else if (draw_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] == TILE_COVER)
                    {
                        // Only place a flag if the tile is covered
                        draw_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] = TILE_FLAG;
                    }
                }
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mousePos{sf::Mouse::getPosition(window)};
                    if (draw_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] != TILE_FLAG)
                    {
                        // If the tile is not flagged, reveal it
                        draw_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] = TILE_EMPTY;
                        if (mine_grid[mousePos.x / (TILE_SIZE * SCALE)][mousePos.y / (TILE_SIZE * SCALE)] = TILE_EMPTY){
                        bfs(mousePos.x / (TILE_SIZE * SCALE), mousePos.y / (TILE_SIZE * SCALE), mine_grid);
                    }
                    }
                }
            }
        }

        window.clear(); // Clear the window with black color

        // update

        // draw

        // draw mine grid
        for (int x = 0; x < WIDTH; ++x)
        {
            for (int y = 0; y < HEIGHT; ++y)
            {
                switch (mine_grid[x][y])
                {
                case TILE_COVER:
                    drawTile(window, x, y, tileSprite);
                    break;
                case TILE_EMPTY:
                    drawTile(window, x, y, emptySprite);
                    break;
                case TILE_FLAG:
                    drawTile(window, x, y, tileSprite);
                    drawTile(window, x, y, flagSprite);
                    break;
                case TILE_ONE:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, oneSprite);
                    break;
                case TILE_TWO:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, twoSprite);
                    break;
                case TILE_THREE:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, threeSprite);
                    break;
                case TILE_FOUR:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, fourSprite);
                    break;
                case TILE_FIVE:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, fiveSprite);
                    break;
                case TILE_SIX:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, sixSprite);
                    break;
                case TILE_SEVEN:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, sevenSprite);
                    break;
                case TILE_EIGHT:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, eightSprite);
                    break;
                case TILE_MINE:
                    drawTile(window, x, y, emptySprite);
                    drawTile(window, x, y, mineSprite);
                    break;
                }
            }
        }
        // draw cover grid
        for (int x = 0; x < WIDTH; ++x)
        {
            for (int y = 0; y < HEIGHT; ++y)
            {
                if (draw_grid[x][y] == TILE_COVER)
                {
                    drawTile(window, x, y, tileSprite);
                }
                else if (draw_grid[x][y] == TILE_FLAG)
                {
                    drawTile(window, x, y, tileSprite);
                    drawTile(window, x, y, flagSprite);
                }
                else if (draw_grid[x][y] == TILE_EMPTY)
                {
                    // do nothing, already drawn
                }
            }
        }

        // draw select square
        rect.setPosition(sf::Vector2f{(float)(pos[0] * SCALE * TILE_SIZE), (float)(pos[1] * SCALE * TILE_SIZE)});
        window.draw(rect);

        window.display(); // Display the contents of the window
    }
}
