#include <vector>

class Graphics
{
  public:
    virtual ~Graphics() = default;

    virtual bool init(const char *title, int width, int height) = 0;
    virtual void render(const std::vector<uint8_t> &pixels, int width, int height) = 0;
    virtual bool processEvents() = 0;
    virtual void cleanup() = 0;
};
