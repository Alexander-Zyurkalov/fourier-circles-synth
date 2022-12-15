//
// Created by Alexandr Zyurkalov on 15.12.22.
//

#include "FourierCircle.h"

FourierCircle::FourierCircle(
        const FourierCircle *prevCircle, int windowWidth, int windowHeight,
        float deltaX, float deltaY, float amplitude)
{
    radius = (float)std::min(windowWidth, windowHeight)/10.0f * amplitude;
    center.setXY((float)windowWidth/2.0f, (float)windowHeight/2.0f);
    if (prevCircle != nullptr)
        center = prevCircle->getPointOnArc();
    pointOnArc = center.translated(deltaX * radius, deltaY * radius);
    plotArea.setLeft(center.getX() - radius);
    plotArea.setTop(center.getY() - radius);
    plotArea.setRight(center.getX() + radius);
    plotArea.setBottom(center.getY() + radius);
}

void FourierCircle::paint(juce::Graphics &g) {
    g.setColour (juce::Colours::yellow);
    g.drawEllipse(plotArea, 1);
}

const juce::Point<float> &FourierCircle::getPointOnArc() const {
    return pointOnArc;
}
