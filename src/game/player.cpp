#include "include/player.h"

/**
 * Sets the player's ID.
 * Player's ID has to be 0 or 1.
 * The ID represents the player in the game.
 *
 * @param id  desired player ID. Has to be 0 or 1.
 */
void Player::setId(int id) {
    id_ = id;
}

/**
 * Returns this player's ID.
 *
 * @return  this player's ID
 */
int Player::getId() {
    return id_;
}

