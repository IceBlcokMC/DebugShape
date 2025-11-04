#pragma once
#include "debug_shape/api/IDebugShapeDrawer.h"
#include "debug_shape/api/shape/IDebugShape.h"

namespace debug_shape::detail {


class DebugShapeDrawerImpl final : public IDebugShapeDrawer {
    void drawer(std::vector<IDebugShape const*> const& shapes, Player* player = nullptr);
    void deleter(std::vector<IDebugShape const*> const& shapes, Player* player = nullptr);

public:
    DS_DISABLE_COPY_MOVE(DebugShapeDrawerImpl);

    static DebugShapeDrawerImpl& getInstance();

    DebugShapeDrawerImpl();
    ~DebugShapeDrawerImpl() override;

    void drawShape(IDebugShape const* shape) override;

    void removeShape(IDebugShape const* shape) override;
    void drawShape(const IDebugShape* shape, Player& player) override;
    void removeShape(const IDebugShape* shape, Player& player) override;
    void drawShapes(const std::vector<IDebugShape const*>& shapes) override;
    void drawShapes(const std::vector<IDebugShape const*>& shapes, Player& player) override;
    void removeShapes(const std::vector<IDebugShape const*>& shapes) override;
    void removeShapes(const std::vector<IDebugShape const*>& shapes, Player& player) override;
};


} // namespace debug_shape::detail