#include "game.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

int main() {
    if (!al_init()) {
        printf("couldn't initialize allegro\n");
        return 1;
    }

    if (!al_init_primitives_addon()) {
        printf("couldn't initialize allegro primitives\n");
    }

    if (!al_install_keyboard() || !al_install_mouse()) {
        printf("couldn't initialize keyboard\n");
        return 1;
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    if (!timer) {
        printf("couldn't initialize timer\n");
        return 1;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue) {
        printf("couldn't initialize queue\n");
        return 1;
    }

    ALLEGRO_DISPLAY *disp = al_create_display(640, 480);
    if (!disp) {
        printf("couldn't initialize display\n");
        return 1;
    }

    ALLEGRO_FONT *font = al_create_builtin_font();
    if (!font) {
        printf("couldn't initialize font\n");
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    std::vector<Work> works;
    Map map = Map(64, 64);
    Agent a = Agent(pos2d(30, 30));

    al_start_timer(timer);
    while (1) {
        al_wait_for_event(queue, &event);

        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state);
        auto mouse = pos2d(state.x / 10, state.y / 10);
        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            if (state.buttons & 1) {
                map.put(mouse, Tile(false, 1, "", false));
            }
            if (state.buttons & 2) {
                map.put(mouse, Tile(true, 1, "", true));
            }
            if (state.buttons & 4) {
                works.push_back(Work(1, mouse, pos2d(40, 40)));
            }
            redraw = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            map.draw();
            a.step(&map, &works);
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}