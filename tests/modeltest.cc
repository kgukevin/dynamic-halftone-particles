#include <core/model.h>

#include <catch2/catch.hpp>

#include "cinder/gl/gl.h"

TEST_CASE("Add Particle") {
  SECTION("Empty initial model", "[constructor]") {
    idealgas::Model model(glm::vec2(0, 0), glm::vec2(20, 20));
    idealgas::Particle new_particle(glm::vec2(10, 10), glm::vec2(10, 0), 10);

    model.AddParticle(new_particle);
    REQUIRE(model.get_particles().size() == 1);
    REQUIRE(model.get_particles()[0].radius() == 10);
    REQUIRE(model.get_particles()[0].position() == glm::vec2(10, 10));
    REQUIRE(model.get_particles()[0].velocity() == glm::vec2(10, 0));
  }

  SECTION("Filled initial model", "[constructor]") {
    idealgas::Particle new_particle(glm::vec2(10, 10), glm::vec2(10, 0), 10);
    idealgas::Particle new_particle2(glm::vec2(11, 11), glm::vec2(11, 0), 10);
    idealgas::Particle new_particle3(glm::vec2(12, 12), glm::vec2(12, 0), 10);
    std::vector<idealgas::Particle> particles{new_particle, new_particle2};
    idealgas::Model model(glm::vec2(0, 0), glm::vec2(20, 20), particles);

    model.AddParticle(new_particle3);
    REQUIRE(model.get_particles().size() == 3);
    REQUIRE(model.get_particles()[0].radius() == 10);
    REQUIRE(model.get_particles()[0].position() == glm::vec2(10, 10));
    REQUIRE(model.get_particles()[0].velocity() == glm::vec2(10, 0));

    REQUIRE(model.get_particles()[1].radius() == 10);
    REQUIRE(model.get_particles()[1].position() == glm::vec2(11, 11));
    REQUIRE(model.get_particles()[1].velocity() == glm::vec2(11, 0));

    REQUIRE(model.get_particles()[2].radius() == 10);
    REQUIRE(model.get_particles()[2].position() == glm::vec2(12, 12));
    REQUIRE(model.get_particles()[2].velocity() == glm::vec2(12, 0));
  }
}

TEST_CASE("Update (collisions testing)") {
  idealgas::Model model(glm::vec2(0, 0), glm::vec2(30, 30));
  SECTION("Wall collisions") {
    SECTION("In range for bounce") {
      SECTION("Left Wall") {
        SECTION("Towards") {
          idealgas::Particle new_particle(glm::vec2(10, 11), glm::vec2(-1, 1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, 1));
        }

        SECTION("Away", "[Particle::UpdatePosition]") {
          idealgas::Particle new_particle(glm::vec2(10, 10), glm::vec2(1, 1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, 1));
        }
      }

      SECTION("Right Wall") {
        SECTION("Towards") {
          idealgas::Particle new_particle(glm::vec2(20, 11), glm::vec2(1, 1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(-1, 1));
        }

        SECTION("Away") {
          idealgas::Particle new_particle(glm::vec2(20, 10), glm::vec2(-1, 1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(-1, 1));
        }
      }

      SECTION("Top Wall") {
        SECTION("Towards") {
          idealgas::Particle new_particle(glm::vec2(11, 10), glm::vec2(1, -1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, 1));
        }

        SECTION("Away") {
          idealgas::Particle new_particle(glm::vec2(11, 10), glm::vec2(1, 1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, 1));
        }
      }

      SECTION("Bottom Wall") {
        SECTION("Towards") {
          idealgas::Particle new_particle(glm::vec2(10, 20), glm::vec2(1, 1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, -1));
        }

        SECTION("Away") {
          idealgas::Particle new_particle(glm::vec2(10, 20), glm::vec2(1, -1),
                                          10);
          model.AddParticle(new_particle);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, -1));
        }
      }

      SECTION("Corners") {
        SECTION("Top left") {
          SECTION("Towards") {
            idealgas::Particle new_particle(glm::vec2(10, 10),
                                            glm::vec2(-1, -1), 10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, 1));
          }

          SECTION("Away") {
            idealgas::Particle new_particle(glm::vec2(10, 10), glm::vec2(1, 1),
                                            10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, 1));
          }
        }

        SECTION("Top right") {
          SECTION("Towards") {
            idealgas::Particle new_particle(glm::vec2(20, 10), glm::vec2(1, -1),
                                            10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(-1, 1));
          }

          SECTION("Away") {
            idealgas::Particle new_particle(glm::vec2(20, 10), glm::vec2(-1, 1),
                                            10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(-1, 1));
          }
        }

        SECTION("Bottom left") {
          SECTION("Towards") {
            idealgas::Particle new_particle(glm::vec2(10, 20), glm::vec2(-1, 1),
                                            10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, -1));
          }

          SECTION("Away") {
            idealgas::Particle new_particle(glm::vec2(10, 20), glm::vec2(1, -1),
                                            10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(1, -1));
          }
        }

        SECTION("Bottom right") {
          SECTION("Towards") {
            idealgas::Particle new_particle(glm::vec2(20, 20), glm::vec2(1, 1),
                                            10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(-1, -1));
          }

          SECTION("Away") {
            idealgas::Particle new_particle(glm::vec2(20, 20),
                                            glm::vec2(-1, -1), 10);
            model.AddParticle(new_particle);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity() == glm::vec2(-1, -1));
          }
        }
      }
    }

    SECTION("Out of bounce range") {
      idealgas::Particle new_particle(glm::vec2(15, 15),
                                      glm::vec2(-112201, 123456), 10);
      model.AddParticle(new_particle);
      model.Update();
      REQUIRE(model.get_particles()[0].velocity() ==
              glm::vec2(-112201, 123456));
    }
  }

  SECTION("Particle collisions") {
    SECTION("Uniform mass") {
      SECTION("2 particles") {
        SECTION("In bounce range") {
          SECTION("Towards") {
            idealgas::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1),
                                            10);
            idealgas::Particle new_particle2(glm::vec2(19, 19),
                                             glm::vec2(-1, -1), 10);
            model.AddParticle(new_particle);
            model.AddParticle(new_particle2);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity().x ==
                    Approx(-1).epsilon(.0001));
            REQUIRE(model.get_particles()[0].velocity().y ==
                    Approx(-1).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().x ==
                    Approx(1).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().y ==
                    Approx(1).epsilon(.0001));
          }

          SECTION("Away") {
            idealgas::Particle new_particle(glm::vec2(11, 11),
                                            glm::vec2(-1, -1), 10);
            idealgas::Particle new_particle2(glm::vec2(19, 19), glm::vec2(1, 1),
                                             1);
            model.AddParticle(new_particle);
            model.AddParticle(new_particle2);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity().x ==
                    Approx(-1).epsilon(.0001));
            REQUIRE(model.get_particles()[0].velocity().y ==
                    Approx(-1).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().x ==
                    Approx(1).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().y ==
                    Approx(1).epsilon(.0001));
          }
        }

        SECTION("Out of bounce range") {
          idealgas::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1),
                                          1);
          idealgas::Particle new_particle2(glm::vec2(19, 19), glm::vec2(-1, -1),
                                           1);
          model.AddParticle(new_particle);
          model.AddParticle(new_particle2);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity().x ==
                  Approx(1).epsilon(.0001));
          REQUIRE(model.get_particles()[0].velocity().y ==
                  Approx(1).epsilon(.0001));
          REQUIRE(model.get_particles()[1].velocity().x ==
                  Approx(-1).epsilon(.0001));
          REQUIRE(model.get_particles()[1].velocity().y ==
                  Approx(-1).epsilon(.0001));
        }
      }
    }
    SECTION("Varied mass") {
      SECTION("2 particles") {
        SECTION("In bounce range") {
          SECTION("Towards") {
            idealgas::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1),
                                            10, 1, "white");
            idealgas::Particle new_particle2(
                glm::vec2(19, 19), glm::vec2(-1, -1), 10, 10, "white");
            model.AddParticle(new_particle);
            model.AddParticle(new_particle2);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity().x ==
                    Approx(-2.6363).epsilon(.0001));
            REQUIRE(model.get_particles()[0].velocity().y ==
                    Approx(-2.6363).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().x ==
                    Approx(-0.6363).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().y ==
                    Approx(-0.6363).epsilon(.0001));
          }

          SECTION("Away") {
            idealgas::Particle new_particle(glm::vec2(11, 11),
                                            glm::vec2(-1, -1), 10, 1, "white");
            idealgas::Particle new_particle2(glm::vec2(19, 19), glm::vec2(1, 1),
                                             1, 10, "white");
            model.AddParticle(new_particle);
            model.AddParticle(new_particle2);
            model.Update();
            REQUIRE(model.get_particles()[0].velocity().x ==
                    Approx(-1).epsilon(.0001));
            REQUIRE(model.get_particles()[0].velocity().y ==
                    Approx(-1).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().x ==
                    Approx(1).epsilon(.0001));
            REQUIRE(model.get_particles()[1].velocity().y ==
                    Approx(1).epsilon(.0001));
          }
        }

        SECTION("Out of bounce range") {
          idealgas::Particle new_particle(glm::vec2(11, 11), glm::vec2(1, 1), 1,
                                          1, "white");
          idealgas::Particle new_particle2(glm::vec2(19, 19), glm::vec2(-1, -1),
                                           1, 10, "white");
          model.AddParticle(new_particle);
          model.AddParticle(new_particle2);
          model.Update();
          REQUIRE(model.get_particles()[0].velocity().x ==
                  Approx(1).epsilon(.0001));
          REQUIRE(model.get_particles()[0].velocity().y ==
                  Approx(1).epsilon(.0001));
          REQUIRE(model.get_particles()[1].velocity().x ==
                  Approx(-1).epsilon(.0001));
          REQUIRE(model.get_particles()[1].velocity().y ==
                  Approx(-1).epsilon(.0001));
        }
      }
    }
  }

  SECTION("Particle between particle and wall") {
    idealgas::Particle new_particle(glm::vec2(11, 11), glm::vec2(-1, -1), 10, 1,
                                    "white");
    idealgas::Particle new_particle2(glm::vec2(20, 20), glm::vec2(1, 1), 10, 10,
                                     "white");
    model.AddParticle(new_particle);
    model.AddParticle(new_particle2);
    model.Update();
    REQUIRE(model.get_particles()[0].velocity().x == Approx(-1).epsilon(.0001));
    REQUIRE(model.get_particles()[0].velocity().y == Approx(-1).epsilon(.0001));
    REQUIRE(model.get_particles()[1].velocity().x == Approx(-1).epsilon(.0001));
    REQUIRE(model.get_particles()[1].velocity().y == Approx(-1).epsilon(.0001));
  }
}

TEST_CASE("Velocity toggle") {
  idealgas::Particle new_particle(glm::vec2(10, 10), glm::vec2(10, 1), 10);
  idealgas::Particle new_particle2(glm::vec2(11, 11), glm::vec2(1, 10), 10);
  idealgas::Particle new_particle3(glm::vec2(12, 12), glm::vec2(10, 10), 10);
  std::vector<idealgas::Particle> particles{new_particle, new_particle2,
                                            new_particle3};
  idealgas::Model model(glm::vec2(0, 0), glm::vec2(20, 20), particles);
  SECTION("Increase velocity") {
    model.IncreaseVelocity();

    idealgas::Particle new_particle4(glm::vec2(10, 10), glm::vec2(12, 1.2), 10);
    idealgas::Particle new_particle5(glm::vec2(11, 11), glm::vec2(1.2, 12), 10);
    idealgas::Particle new_particle6(glm::vec2(12, 12), glm::vec2(12, 12), 10);
    std::vector<idealgas::Particle> particles2{new_particle4, new_particle5,
                                               new_particle6};
    for (size_t index = 0; index < model.get_particles().size(); index++) {
      REQUIRE(model.get_particles()[index].velocity() ==
              particles2[index].velocity());
    }
  }

  SECTION("Decrease velocity") {
    model.DecreaseVelocity();

    idealgas::Particle new_particle4(glm::vec2(10, 10), glm::vec2(8, .8), 10);
    idealgas::Particle new_particle5(glm::vec2(11, 11), glm::vec2(.8, 8), 10);
    idealgas::Particle new_particle6(glm::vec2(12, 12), glm::vec2(8, 8), 10);
    std::vector<idealgas::Particle> particles2{new_particle4, new_particle5,
                                               new_particle6};
    for (size_t index = 0; index < model.get_particles().size(); index++) {
      REQUIRE(model.get_particles()[index].velocity() ==
              particles2[index].velocity());
    }
  }
}

TEST_CASE("CreteVelHistogramData") {
  idealgas::Particle new_particle(glm::vec2(10, 10), glm::vec2(7, 0), 10, 1,
                                  "red");
  idealgas::Particle new_particle2(glm::vec2(11, 11), glm::vec2(0, 0), 10, 1,
                                   "red");
  idealgas::Particle new_particle3(glm::vec2(0, 2), glm::vec2(12, 0), 10, 1,
                                   "red");
  std::vector<idealgas::Particle> particles{new_particle, new_particle2,
                                            new_particle3};
  idealgas::Model model(glm::vec2(0, 0), glm::vec2(20, 20), particles);
  std::vector<float> vec{7, 0, 12};
  std::map<std::string, std::vector<float>> expected = {{"red", vec}};
  REQUIRE(model.CreateVelHistogramData() == expected);
}
