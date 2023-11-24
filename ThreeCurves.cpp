#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "tbb/tbb.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector3.h"
#include "Curve.h"
#include "Utility.h"
#include "Circle.h"
#include "Ell.h"
#include "Helix.h"

bool CompareCircles(std::shared_ptr<Curve> c1, std::shared_ptr<Curve> c2)
{
    return (std::static_pointer_cast<Circle>(c1)->GetRadius() < std::static_pointer_cast<Circle>(c2)->GetRadius());
}


int main()
{
    srand(time(NULL));

//2
    std::vector<std::shared_ptr<Curve>> the_first_container;

    for (auto i = 0; i < CURVES_COUNT; i++)
    {
        std::shared_ptr<Curve> curve_ptr;
        switch (rand() % 3)
        {
        case 0:
            {
            float r = MIN_CIRCLE_R + rand() / (RAND_MAX / (MAX_CIRCLE_R - MIN_CIRCLE_R));
            curve_ptr = std::shared_ptr<Curve>(new Circle(r));
            break;
            }
        case 1:
            {
            float r1 = MIN_ELLIPSE_R1 + rand() / (RAND_MAX / (MAX_ELLIPSE_R1 - MIN_ELLIPSE_R1));
            float r2 = MIN_ELLIPSE_R2 + rand() / (RAND_MAX / (MAX_ELLIPSE_R2 - MIN_ELLIPSE_R2));
            curve_ptr = std::shared_ptr<Curve>(new Ell(r1, r2));
            break;
            }
        default:
            {
            float r = MIN_HELIX_R + rand() / (RAND_MAX / (MAX_HELIX_R - MIN_HELIX_R));
            float s = MIN_HELIX_S + rand() / (RAND_MAX / (MAX_HELIX_S - MIN_HELIX_S));
            curve_ptr = std::shared_ptr<Curve>(new Helix(r, s));
            }
        }
        the_first_container.push_back(curve_ptr);
    }

//3
    std::cout << "Points and derivative vectors of " << CURVES_COUNT << " curves:" << std::endl << std::endl;

    for (auto const &curve : the_first_container)
    {
        Vector3 p = curve->GetPoint(M_PI_4);
        Vector3 fd = curve->GetFirstDerivativeVector(M_PI_4);

        std::cout << "Point at PI/4: " << p.x << ", " << p.y << ", " << p.z << std::endl;
        std::cout << "First derivative vector at PI/4: " << fd.x << ", " << fd.y << ", " << fd.z << std::endl;
        std::cout << "-------------" << std::endl;
    }

//4
    std::vector<std::shared_ptr<Curve>> a_second_container;

    for (auto const &curve : the_first_container)
    {
        if(curve->GetType() == CurveType::CIRCLE) a_second_container.push_back(curve);
    }

//5
    std::cout << std::endl << "A second container before sorting:" << std::endl << std::endl;

    for (auto const& curve : a_second_container)
    {
        std::cout << std::static_pointer_cast<Circle>(curve)->GetRadius() << "  ";
    }
    std::cout << std::endl;

    sort(a_second_container.begin(), a_second_container.end(), CompareCircles);

    std::cout << std::endl << "A second container after sorting:" << std::endl << std::endl;

    for (auto const& curve : a_second_container)
    {
        std::cout << std::static_pointer_cast<Circle>(curve)->GetRadius() << "  ";
    }
    std::cout << std::endl;

//6
    float sum_of_radii = 0;

    /*
    std::for_each(a_second_container.begin(), a_second_container.end(), [&](auto const& curve) {
        sum_of_radii += std::static_pointer_cast<Circle>(curve)->GetRadius();
        });

    std::cout << std::endl << "Total sum of radii: " << sum_of_radii << std::endl << std::endl;
    */

    /*
    sum_of_radii = std::accumulate(a_second_container.begin(), a_second_container.end(), 0.0f, [](float accumulator, auto const& curve) {
        return accumulator + std::static_pointer_cast<Circle>(curve)->GetRadius();
        });

    std::cout << std::endl << "Total sum of radii: " << sum_of_radii << std::endl << std::endl;
    */


    class Sum
    {
    public:
        auto operator ()(std::shared_ptr<Curve> &curve) const noexcept
        {
            return std::static_pointer_cast<Circle>(curve)->GetRadius();
        }

        auto operator ()(float const& accum1, float const& accum2) const noexcept
        {
            return accum1 + accum2;
        }

        auto operator ()(std::shared_ptr<Curve> &curve, float const accum) const noexcept
        {
            return accum + std::static_pointer_cast<Circle>(curve)->GetRadius();
        }

        auto operator ()(float const accum, std::shared_ptr<Curve> &curve) const noexcept
        {
            return accum + std::static_pointer_cast<Circle>(curve)->GetRadius();
        }

        auto operator ()(std::shared_ptr<Curve> &curve1, std::shared_ptr<Curve> &curve2) const noexcept
        {
            return std::static_pointer_cast<Circle>(curve1)->GetRadius() + std::static_pointer_cast<Circle>(curve2)->GetRadius();
        }
    };


    sum_of_radii = std::reduce(a_second_container.begin(), a_second_container.end(), 0.0f, Sum());

    std::cout << std::endl << std::endl << "Total sum of radii: " << sum_of_radii << std::endl << std::endl;

//8
    typedef tbb::blocked_range<std::vector<std::shared_ptr<Curve>>::iterator> range_type;

    struct Sum2 {
        float value;

        Sum2() : value(0.0f) {}
        Sum2(Sum2& s, tbb::split) : value(0.0f) {}

        void operator()(const range_type& r)
        {
            value = std::accumulate(r.begin(), r.end(), value, [](float accumulator, auto const& curve) {
                return accumulator + std::static_pointer_cast<Circle>(curve)->GetRadius();
                });
        }

        void join(Sum2& rhs)
        {
            value += rhs.value;
        }
    };

    Sum2 sum;
    tbb::parallel_reduce(range_type(a_second_container.begin(), a_second_container.end()), sum);
    
    std::cout << std::endl << "Total sum of radii, calculated using Intel TBB: " << sum.value << std::endl << std::endl;

    std::cin.get();
}

