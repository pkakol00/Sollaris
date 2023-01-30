#include "gtest/gtest.h"
#include "../src/physics/PhysicsEngine.h"


PhysicsEngine prepare_system(std::shared_ptr<std::vector<PlanetPosition>> &position, std::shared_ptr<std::vector<PlanetData>> &data, int interval) {
                                // id      Position (m)  x,   y,            z
    PlanetPosition ap; ap.planet_id = 0; ap.positions.push_back({0.0,                0.0, 0.0}); // Sun
    PlanetPosition bp; bp.planet_id = 1; bp.positions.push_back({0.0,    +57'909'036'552, 0.0}); // Mercury
    PlanetPosition cp; cp.planet_id = 2; cp.positions.push_back({0.0,   -108'207'927'552, 0.0}); // Venus
    PlanetPosition dp; dp.planet_id = 3; dp.positions.push_back({0.0,   +149'598'023'000, 0.0}); // Earth
    PlanetPosition ep; ep.planet_id = 4; ep.positions.push_back({0.0,   -227'939'366'000, 0.0}); // Mars
    PlanetPosition fp; fp.planet_id = 5; fp.positions.push_back({0.0,   +778'479'399'549, 0.0}); // Jupiter
    PlanetPosition gp; gp.planet_id = 6; gp.positions.push_back({0.0, -1'433'536'555'770, 0.0}); // Saturn
    PlanetPosition hp; hp.planet_id = 7; hp.positions.push_back({0.0, +2'870'971'632'050, 0.0}); // Uranus
    PlanetPosition ip; ip.planet_id = 8; ip.positions.push_back({0.0, -4'498'407'971'949, 0.0}); // Neptune

                // Mass (kg)  Radious (m)   Velocity (m/s)       Color      id
    PlanetData ad {1.98910e30, 6.95508e8, {    0.0, 0.0, 0.0}, {0.1, 0.5, 0.2}, 0}; // Sun
    PlanetData bd {6.41710e23, 3.38950e6, {+47'360, 0.0, 0.0}, {0.2, 0.6, 0.4}, 1}; // Mercury
    PlanetData cd {4.86750e24, 6.06200e6, {-35'020, 0.0, 0.0}, {0.2, 0.6, 0.4}, 2}; // Venus
    PlanetData dd {5.97217e24, 6.37100e6, {+29'780, 0.0, 0.0}, {0.2, 0.6, 0.4}, 3}; // Earth
    PlanetData ed {6.41710e23, 3.38950e6, {-24'070, 0.0, 0.0}, {0.3, 0.7, 0.6}, 4}; // Mars
    PlanetData fd {1.89887e27, 6.99110e7, {+13'070, 0.0, 0.0}, {0.4, 0.1, 0.8}, 5}; // Jupiter
    PlanetData gd {5.68317e26, 5.82320e7, { -9'680, 0.0, 0.0}, {0.5, 0.2, 0.1}, 6}; // Saturn
    PlanetData hd {8.68130e25, 2.53620e7, { +6'800, 0.0, 0.0}, {0.6, 0.3, 0.3}, 7}; // Uranus
    PlanetData id {1.02413e26, 2.46220e7, { -5'430, 0.0, 0.0}, {0.7, 0.4, 0.5}, 8}; // Neptune

    position = std::make_shared<std::vector<PlanetPosition>>(std::initializer_list<PlanetPosition>{ap, bp, cp, dp, ep, fp, gp, hp, ip});
    data = std::make_shared<std::vector<PlanetData>>(std::initializer_list<PlanetData>{ad, bd, cd, dd, ed, fd, gd, hd, id});

    return PhysicsEngine(position, data, interval);
}

double calc_momentum(const std::shared_ptr<std::vector<PlanetData>> &data) {
    double momentum = 0.0;
    for(const auto &planet : *data) {
        momentum += planet.mass * (planet.velocity).length();
    }

    return momentum;
}

TEST(PhysicsEngineTest, ConstantMomentumSum) {
    std::shared_ptr<std::vector<PlanetPosition>> position;
    std::shared_ptr<std::vector<PlanetData>> data;
    const double interval = 1;

    auto PE = prepare_system(position, data, interval);

    double org_momentum = calc_momentum(data);

    for(int i = 0; i < 1'000; ++i) {
        PE.update();
        double momentum = calc_momentum(data);
        EXPECT_NEAR(momentum / org_momentum, 1.0, 0.001);
    }
}

Vec3 calc_barycenter(const std::shared_ptr<std::vector<PlanetPosition>> &position, const std::shared_ptr<std::vector<PlanetData>> &data) {
    Vec3 barycenter {0.0, 0.0, 0.0};
    double mass_sum = 0.0;

    for(int i = 0; i < position->size(); ++i) {
        mass_sum += data->at(i).mass;
        barycenter += position->at(i).positions.back() * data->at(i).mass;
    }

    return barycenter / mass_sum;
}

TEST(PhysicsEngineTest, Barycenter) {
    std::shared_ptr<std::vector<PlanetPosition>> position;
    std::shared_ptr<std::vector<PlanetData>> data;
    const double interval = 1;

    auto PE = prepare_system(position, data, interval);

    Vec3 first_barycenter  = calc_barycenter(position, data);
    PE.update();
    Vec3 second_barycenter = calc_barycenter(position, data);

    Vec3 org_diff = second_barycenter - first_barycenter;
    Vec3 prev_barycenter = second_barycenter;

    for(int i = 0; i < 1'000; ++i) {
        PE.update();

        Vec3 barycenter = calc_barycenter(position, data);
        Vec3 diff = barycenter - prev_barycenter;

        EXPECT_NEAR(diff.x, org_diff.x, 0.1);
        EXPECT_NEAR(diff.y, org_diff.y, 0.1);
        EXPECT_NEAR(diff.z, org_diff.z, 0.1);

        prev_barycenter = barycenter;
    }
}

TEST(PhysicsEngineTest, ShouldNotCollide) {
    std::shared_ptr<std::vector<PlanetPosition>> position;
    std::shared_ptr<std::vector<PlanetData>> data;
    const double interval = 1;
    auto PE = prepare_system(position, data, interval);

    bool detected = false;
    std::vector<int> old_planets;
    int new_planet = -1;

    auto callback = [&detected, &old_planets, &new_planet](std::vector<int> old_ids, int new_id) {
        detected = true;
        old_planets = old_ids;
        new_planet = new_id;
    };

    PE.subscribe_to_planet_merge(callback);

    for(int i = 0; i < 100; ++i) {
        PE.update();
        EXPECT_EQ(detected, false);
        EXPECT_EQ(new_planet, -1);
        EXPECT_EQ(old_planets.size(), 0);
    }
}

TEST(PhysicsEngineTest, ShouldCollide) {
    PlanetPosition ap; ap.planet_id = 0; ap.positions.push_back({+500, 0, 0});
    PlanetPosition bp; bp.planet_id = 1; bp.positions.push_back({-1'000, -1'000, 0});
    auto position = std::make_shared<std::vector<PlanetPosition>>(std::initializer_list<PlanetPosition>{ap, bp});
    int next_id = bp.planet_id + 1;

    PlanetData ad {1e1, 5, {-5.0, 0.0, 0.0}, {0.1, 0.2, 0.9}, 0};
    PlanetData bd {1e1, 5, {10.0, 10.0, 0.0}, {0.9, 0.2, 0.3}, 1};
    auto data = std::make_shared<std::vector<PlanetData>>(std::initializer_list<PlanetData>{ad, bd});

    const double interval = 1;
    auto PE = PhysicsEngine(position, data, interval);

    bool detected = false;
    std::vector<int> old_planets;
    int new_planet = -1;

    auto callback = [&detected, &old_planets, &new_planet](std::vector<int> old_ids, int new_id) {
        detected = true;
        old_planets = old_ids;
        new_planet = new_id;
    };

    PE.subscribe_to_planet_merge(callback);

    // There should be no collision for 99 iterations
    for(int i = 0; i < 99; ++i) {
        PE.update();
        EXPECT_EQ(detected, false);
        EXPECT_EQ(new_planet, -1);
        EXPECT_EQ(old_planets.size(), 0);
    }

    // In 100th iteration two planets should collide and procude new planet
    PE.update();
    EXPECT_EQ(detected, true);
    EXPECT_EQ(new_planet, next_id);
    EXPECT_EQ(old_planets.size(), 2);

    // We acknowledged collision
    detected = false;
    new_planet = -1;
    old_planets.clear();

    // There should be no further collisions
    for(int i = 0; i < 1'000; ++i) {
        PE.update();
        EXPECT_EQ(detected, false);
        EXPECT_EQ(new_planet, -1);
        EXPECT_EQ(old_planets.size(), 0);
    }
}
