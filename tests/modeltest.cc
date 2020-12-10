#include <core/model.h>

#include <catch2/catch.hpp>

#include "cinder/gl/gl.h"

TEST_CASE("Add Particle") {
    SECTION("Empty initial model", "[constructor]") {
        halftoneparticle::Model model(glm::vec2(0, 0), glm::vec2(20, 20));
        halftoneparticle::Particle new_particle(glm::vec2(10, 10), glm::vec2(10, 0), 10);

        model.AddParticle(new_particle);
        REQUIRE(model.GetParticles().size() == 1);
        REQUIRE(model.GetParticles()[0].radius() == 10);
        REQUIRE(model.GetParticles()[0].position() == glm::vec2(10, 10));
        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(10, 0));
    }

    SECTION("Filled initial model", "[constructor]") {
        halftoneparticle::Particle new_particle(glm::vec2(10, 10), glm::vec2(10, 0), 10);
        halftoneparticle::Particle new_particle2(glm::vec2(11, 11), glm::vec2(11, 0), 10);
        halftoneparticle::Particle new_particle3(glm::vec2(12, 12), glm::vec2(12, 0), 10);
        std::vector<halftoneparticle::Particle> particles{new_particle, new_particle2};
        halftoneparticle::Model model(glm::vec2(0, 0), glm::vec2(20, 20), particles);

        model.AddParticle(new_particle3);
        REQUIRE(model.GetParticles().size() == 3);
        REQUIRE(model.GetParticles()[0].radius() == 10);
        REQUIRE(model.GetParticles()[0].position() == glm::vec2(10, 10));
        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(10, 0));

        REQUIRE(model.GetParticles()[1].radius() == 10);
        REQUIRE(model.GetParticles()[1].position() == glm::vec2(11, 11));
        REQUIRE(model.GetParticles()[1].velocity() == glm::vec2(11, 0));

        REQUIRE(model.GetParticles()[2].radius() == 10);
        REQUIRE(model.GetParticles()[2].position() == glm::vec2(12, 12));
        REQUIRE(model.GetParticles()[2].velocity() == glm::vec2(12, 0));
    }
}

TEST_CASE("Update (collisions testing)") {
    halftoneparticle::Model model(glm::vec2(0, 0), glm::vec2(30, 30));
    SECTION("Wall collisions") {
        SECTION("In range for bounce") {
            SECTION("Left Wall") {
                SECTION("Towards") {
                    halftoneparticle::Particle new_particle(glm::vec2(10, 11), glm::vec2(-1, 1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, 1));
                }

                SECTION("Away", "[Particle::UpdatePosition]") {
                    halftoneparticle::Particle new_particle(glm::vec2(10, 10), glm::vec2(1, 1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, 1));
                }
            }

            SECTION("Right Wall") {
                SECTION("Towards") {
                    halftoneparticle::Particle new_particle(glm::vec2(20, 11), glm::vec2(1, 1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(-1, 1));
                }

                SECTION("Away") {
                    halftoneparticle::Particle new_particle(glm::vec2(20, 10), glm::vec2(-1, 1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(-1, 1));
                }
            }

            SECTION("Top Wall") {
                SECTION("Towards") {
                    halftoneparticle::Particle new_particle(glm::vec2(11, 10), glm::vec2(1, -1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, 1));
                }

                SECTION("Away") {
                    halftoneparticle::Particle new_particle(glm::vec2(11, 10), glm::vec2(1, 1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, 1));
                }
            }

            SECTION("Bottom Wall") {
                SECTION("Towards") {
                    halftoneparticle::Particle new_particle(glm::vec2(10, 20), glm::vec2(1, 1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, -1));
                }

                SECTION("Away") {
                    halftoneparticle::Particle new_particle(glm::vec2(10, 20), glm::vec2(1, -1),
                                                            10);
                    model.AddParticle(new_particle);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, -1));
                }
            }

            SECTION("Corners") {
                SECTION("Top left") {
                    SECTION("Towards") {
                        halftoneparticle::Particle new_particle(glm::vec2(10, 10),
                                                                glm::vec2(-1, -1), 10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, 1));
                    }

                    SECTION("Away") {
                        halftoneparticle::Particle new_particle(glm::vec2(10, 10), glm::vec2(1, 1),
                                                                10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, 1));
                    }
                }

                SECTION("Top right") {
                    SECTION("Towards") {
                        halftoneparticle::Particle new_particle(glm::vec2(20, 10), glm::vec2(1, -1),
                                                                10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(-1, 1));
                    }

                    SECTION("Away") {
                        halftoneparticle::Particle new_particle(glm::vec2(20, 10), glm::vec2(-1, 1),
                                                                10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(-1, 1));
                    }
                }

                SECTION("Bottom left") {
                    SECTION("Towards") {
                        halftoneparticle::Particle new_particle(glm::vec2(10, 20), glm::vec2(-1, 1),
                                                                10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, -1));
                    }

                    SECTION("Away") {
                        halftoneparticle::Particle new_particle(glm::vec2(10, 20), glm::vec2(1, -1),
                                                                10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1, -1));
                    }
                }

                SECTION("Bottom right") {
                    SECTION("Towards") {
                        halftoneparticle::Particle new_particle(glm::vec2(20, 20), glm::vec2(1, 1),
                                                                10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(-1, -1));
                    }

                    SECTION("Away") {
                        halftoneparticle::Particle new_particle(glm::vec2(20, 20),
                                                                glm::vec2(-1, -1), 10);
                        model.AddParticle(new_particle);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(-1, -1));
                    }
                }
            }
        }

        SECTION("Out of bounce range") {
            halftoneparticle::Particle new_particle(glm::vec2(15, 15),
                                                    glm::vec2(-112201, 123456), 10);
            model.AddParticle(new_particle);
            model.UpdateMove();
            REQUIRE(model.GetParticles()[0].velocity() ==
                    glm::vec2(-112201, 123456));
        }
    }

    SECTION("Particle collisions") {
        SECTION("Uniform mass") {
            SECTION("2 particles") {
                SECTION("In bounce range") {
                    SECTION("Towards") {
                        halftoneparticle::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1),
                                                                10);
                        halftoneparticle::Particle new_particle2(glm::vec2(19, 19),
                                                                 glm::vec2(-1, -1), 10);
                        model.AddParticle(new_particle);
                        model.AddParticle(new_particle2);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity().x ==
                                Approx(-1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[0].velocity().y ==
                                Approx(-1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().x ==
                                Approx(1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().y ==
                                Approx(1).epsilon(.0001));
                    }

                    SECTION("Away") {
                        halftoneparticle::Particle new_particle(glm::vec2(11, 11),
                                                                glm::vec2(-1, -1), 10);
                        halftoneparticle::Particle new_particle2(glm::vec2(19, 19), glm::vec2(1, 1),
                                                                 1);
                        model.AddParticle(new_particle);
                        model.AddParticle(new_particle2);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity().x ==
                                Approx(-1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[0].velocity().y ==
                                Approx(-1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().x ==
                                Approx(1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().y ==
                                Approx(1).epsilon(.0001));
                    }
                }

                SECTION("Out of bounce range") {
                    halftoneparticle::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1),
                                                            1);
                    halftoneparticle::Particle new_particle2(glm::vec2(19, 19), glm::vec2(-1, -1),
                                                             1);
                    model.AddParticle(new_particle);
                    model.AddParticle(new_particle2);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity().x ==
                            Approx(1).epsilon(.0001));
                    REQUIRE(model.GetParticles()[0].velocity().y ==
                            Approx(1).epsilon(.0001));
                    REQUIRE(model.GetParticles()[1].velocity().x ==
                            Approx(-1).epsilon(.0001));
                    REQUIRE(model.GetParticles()[1].velocity().y ==
                            Approx(-1).epsilon(.0001));
                }
            }
        }
        SECTION("Varied mass") {
            SECTION("2 particles") {
                SECTION("In bounce range") {
                    SECTION("Towards") {
                        halftoneparticle::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1),
                                                                10, 1, "white");
                        halftoneparticle::Particle new_particle2(
                                glm::vec2(19, 19), glm::vec2(-1, -1), 10, 10, "white");
                        model.AddParticle(new_particle);
                        model.AddParticle(new_particle2);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity().x ==
                                Approx(-2.6363).epsilon(.0001));
                        REQUIRE(model.GetParticles()[0].velocity().y ==
                                Approx(-2.6363).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().x ==
                                Approx(-0.6363).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().y ==
                                Approx(-0.6363).epsilon(.0001));
                    }

                    SECTION("Away") {
                        halftoneparticle::Particle new_particle(glm::vec2(11, 11),
                                                                glm::vec2(-1, -1), 10, 1, "white");
                        halftoneparticle::Particle new_particle2(glm::vec2(19, 19), glm::vec2(1, 1),
                                                                 1, 10, "white");
                        model.AddParticle(new_particle);
                        model.AddParticle(new_particle2);
                        model.UpdateMove();
                        REQUIRE(model.GetParticles()[0].velocity().x ==
                                Approx(-1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[0].velocity().y ==
                                Approx(-1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().x ==
                                Approx(1).epsilon(.0001));
                        REQUIRE(model.GetParticles()[1].velocity().y ==
                                Approx(1).epsilon(.0001));
                    }
                }

                SECTION("Out of bounce range") {
                    halftoneparticle::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1), 1,
                                                            1, "white");
                    halftoneparticle::Particle new_particle2(glm::vec2(19, 19), glm::vec2(-1, -1),
                                                             1, 10, "white");
                    model.AddParticle(new_particle);
                    model.AddParticle(new_particle2);
                    model.UpdateMove();
                    REQUIRE(model.GetParticles()[0].velocity().x ==
                            Approx(1).epsilon(.0001));
                    REQUIRE(model.GetParticles()[0].velocity().y ==
                            Approx(1).epsilon(.0001));
                    REQUIRE(model.GetParticles()[1].velocity().x ==
                            Approx(-1).epsilon(.0001));
                    REQUIRE(model.GetParticles()[1].velocity().y ==
                            Approx(-1).epsilon(.0001));
                }
            }
        }
    }

    SECTION("Particle between particle and wall") {
        halftoneparticle::Particle new_particle(glm::vec2(11, 11), glm::vec2(-1, -1), 10, 1,
                                                "white");
        halftoneparticle::Particle new_particle2(glm::vec2(20, 20), glm::vec2(1, 1), 10, 10,
                                                 "white");
        model.AddParticle(new_particle);
        model.AddParticle(new_particle2);
        model.UpdateMove();
        REQUIRE(model.GetParticles()[0].velocity().x == Approx(-1).epsilon(.0001));
        REQUIRE(model.GetParticles()[0].velocity().y == Approx(-1).epsilon(.0001));
        REQUIRE(model.GetParticles()[1].velocity().x == Approx(-1).epsilon(.0001));
        REQUIRE(model.GetParticles()[1].velocity().y == Approx(-1).epsilon(.0001));
    }
}

TEST_CASE("Velocity toggle") {
    halftoneparticle::Particle new_particle(glm::vec2(10, 10), glm::vec2(10, 1), 10);
    halftoneparticle::Particle new_particle2(glm::vec2(11, 11), glm::vec2(1, 10), 10);
    halftoneparticle::Particle new_particle3(glm::vec2(12, 12), glm::vec2(10, 10), 10);
    std::vector<halftoneparticle::Particle> particles{new_particle, new_particle2,
                                                      new_particle3};
    halftoneparticle::Model model(glm::vec2(0, 0), glm::vec2(20, 20), particles);
    SECTION("Increase velocity") {
        model.IncreaseVelocity();

        halftoneparticle::Particle new_particle4(glm::vec2(10, 10), glm::vec2(12, 1.2), 10);
        halftoneparticle::Particle new_particle5(glm::vec2(11, 11), glm::vec2(1.2, 12), 10);
        halftoneparticle::Particle new_particle6(glm::vec2(12, 12), glm::vec2(12, 12), 10);
        std::vector<halftoneparticle::Particle> particles2{new_particle4, new_particle5,
                                                           new_particle6};
        for (size_t index = 0; index < model.GetParticles().size(); index++) {
            REQUIRE(model.GetParticles()[index].velocity() ==
                    particles2[index].velocity());
        }
    }

    SECTION("Decrease velocity") {
        model.DecreaseVelocity();

        halftoneparticle::Particle new_particle4(glm::vec2(10, 10), glm::vec2(8, .8), 10);
        halftoneparticle::Particle new_particle5(glm::vec2(11, 11), glm::vec2(.8, 8), 10);
        halftoneparticle::Particle new_particle6(glm::vec2(12, 12), glm::vec2(8, 8), 10);
        std::vector<halftoneparticle::Particle> particles2{new_particle4, new_particle5,
                                                           new_particle6};
        for (size_t index = 0; index < model.GetParticles().size(); index++) {
            REQUIRE(model.GetParticles()[index].velocity() ==
                    particles2[index].velocity());
        }
    }
}

TEST_CASE("Gravity") {
    halftoneparticle::Particle new_particle(glm::vec2(10, 10), glm::vec2(1, 1), 10);
    halftoneparticle::Particle new_particle2(glm::vec2(15, 15), glm::vec2(1, 11), 1);
    std::vector<halftoneparticle::Particle> particles{new_particle, new_particle2};
    halftoneparticle::Model model(glm::vec2(0, 0), glm::vec2(20, 20), particles);
    model.SetGravityOrigin(glm::vec2(10,10));
    
    SECTION("At center of gravity"){
        model.GetParticles()[0].UpdateAcceleration(glm::vec2(10,10), 1.0f);
        model.GetParticles()[0].UpdateVelocity();
        REQUIRE(model.GetParticles()[0].velocity() == glm::vec2(1,1));
    }

    SECTION("Off center of gravity") {
        model.GetParticles()[1].UpdateAcceleration(glm::vec2(10,10), 1.0f);
        model.GetParticles()[1].UpdateVelocity();
        REQUIRE(model.GetParticles()[1].velocity() == glm::vec2(1,11));
    }
}