from spacecrafts import Player, Enemy, IceEnemy, FireEnemy, PoisonEnemy
from bullets import FireBullet, IceBullet, PoisonBullet


class Powers:
    def fire(self):
        return FireBullet()

    def ice(self):
        return IceBullet()

    def poison(self):
        return PoisonBullet()


class Crafts:
    def fire(self):
        return Player(bullet=Powers.fire(self))

    def ice(self):
        return Player(bullet=Powers.ice(self))

    def poison(self):
        return Player(bullet=Powers.poison(self))


class Enemies:
    def fire(self):
        return FireEnemy(bullet=Powers.fire(self))

    def ice(self):
        return IceEnemy(bullet=Powers.ice(self))

    def poison(self):
        return PoisonEnemy(bullet=Powers.poison(self))
