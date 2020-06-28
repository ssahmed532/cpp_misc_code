// Part 1 of the Curried Objects series by Jonathan Boccara:
//
//      https://www.fluentcpp.com/2019/05/03/curried-objects-in-cpp/
//

#include <iostream>
#include <cmath>


void drawAt(float x, float y, float z)
{
    std::cout << "x:" << x << ", y:" << y << ", z:" << z << '\n';
}


void drawInPlaneAt(float x, float y)
{
    drawAt(x, y, 0);
}


auto drawOnLine(float slope, float yIntercept)
{
    return
        [slope, yIntercept](float x)
        {
            drawAt(x, (slope * x) + yIntercept, 0);
        };
}


auto drawOnCircle(float xCenter, float yCenter, float radius)
{
    return [xCenter, yCenter, radius](float angle)
    {
        const float xFromCenter = radius * std::sin(angle);
        const float yFromCenter = radius * std::cos(angle);
        drawInPlaneAt(xCenter + xFromCenter, yCenter + yFromCenter);
    };
}


int main()
{
    {
        // draw each of the four cardinal points in the plane at z=0.
        drawAt(1, 0, 0);
        drawAt(0, 1, 0);
        drawAt(-1, 0, 0);
        drawAt(0, -1, 0);
        std::cout << '\n';
        std::cout << '\n';
    }

    {
        // lambda for partial currying
        auto drawInPlaneAt =
        [](float x, float y)
        {
            drawAt(x, y, 0);
        };

        drawInPlaneAt(1, 0);
        drawInPlaneAt(0, 1);
        drawInPlaneAt(-1, 0);
        drawInPlaneAt(0, -1);
        std::cout << '\n';
        std::cout << '\n';
    }

    {
        // draw a line of points identified by a slope and an y-intercept
        auto drawOnMyLine = drawOnLine(0.5, 3);
        for (float x = -5; x < 6; x +=1)
        {
            drawOnMyLine(x);
        }
        std::cout << '\n';
        std::cout << '\n';
    }

    {
        // draw a circle identified by polar co-ordinates
        auto drawOnMyCircle = drawOnCircle(2, 1, 3);
        for (float angle = -3.14; angle < 3.14; angle += 0.2)
        {
            drawOnMyCircle(angle);
        }
    }

    return 0;
}
