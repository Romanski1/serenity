#pragma once

#include <LibGUI/GWidget.h>
class Tool;

class PaintableWidget final : public GWidget {
public:
    static PaintableWidget& the();

    explicit PaintableWidget(GWidget* parent);
    virtual ~PaintableWidget() override;

    virtual const char* class_name() const override { return "PaintableWidget"; }

    Color primary_color() const { return m_primary_color; }
    Color secondary_color() const { return m_secondary_color; }

    void set_primary_color(Color);
    void set_secondary_color(Color);

    void set_tool(Tool* tool);
    Tool* tool();

    Color color_for(const GMouseEvent&);

    GraphicsBitmap& bitmap() { return *m_bitmap; }
    const GraphicsBitmap& bitmap() const { return *m_bitmap; }

    Function<void(Color)> on_primary_color_change;
    Function<void(Color)> on_secondary_color_change;

private:
    virtual void paint_event(GPaintEvent&) override;
    virtual void mousedown_event(GMouseEvent&) override;
    virtual void mouseup_event(GMouseEvent&) override;
    virtual void mousemove_event(GMouseEvent&) override;

    RefPtr<GraphicsBitmap> m_bitmap;

    Color m_primary_color { Color::Black };
    Color m_secondary_color { Color::White };

    Tool* m_tool { nullptr };
};
