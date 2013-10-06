#include "stdafx.h"
#include "Factory.h"
#include "RectangleMarker.h"
#include "VerticalRectangleMarker.h"
#include "PolygonMarker.h"


GateDrawing::IGateDrawing^ GateDrawing::Factory::CreateGateDrawing( GateDrawing::PlotMarkerType markerType )
{
    switch (markerType)
    {
    case PlotMarkerType::Polygon:
        return gcnew GateDrawing::PolygonMarker;
    case PlotMarkerType::Rectangle:
        return gcnew RectangleMarker();
    case PlotMarkerType::Stripe:
        return gcnew VerticalRectangleMarker();
    }
    return nullptr;
}
