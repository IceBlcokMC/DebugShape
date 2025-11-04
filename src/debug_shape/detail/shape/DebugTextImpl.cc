#include "DebugTextImpl.h"

namespace debug_shape {

std::unique_ptr<IDebugText> IDebugText::create(Vec3 const& loc, std::string const& text) {
    return std::make_unique<detail::DebugTextImpl>(loc, text);
}

namespace detail {

DebugTextImpl::DebugTextImpl(Vec3 const& loc, std::string const& text) : DebugShapeImpl(ShapeType::Text, loc) {
    TextDataPayload extra{};
    extra.mText                = text;
    payload_.mExtraDataPayload = std::move(extra);
}

std::string DebugTextImpl::getText() const {
    return std::get<TextDataPayload>(payload_.mExtraDataPayload.get()).mText.get();
}

void DebugTextImpl::setText(const std::string& txt) {
    std::get<TextDataPayload>(payload_.mExtraDataPayload.get()).mText = txt;
}

} // namespace detail

} // namespace debug_shape