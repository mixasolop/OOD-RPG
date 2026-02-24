using namespace std;


class World;
class Player;

class Renderer {
public:
    Renderer();
    void draw(const World& world, const Player& player) const;
};