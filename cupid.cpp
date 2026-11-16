#include <iostream>
#include <vector>
#include <string>
#include <random>

struct Fruit {
    std::string name {""};
    int rarity {0};
};

struct Item {
    std::string itemName {""};
    int Itemrarity {0};
};

void dungeons(
    std::mt19937& RNG,
    std::discrete_distribution<>& drop,
    std::discrete_distribution<>& item,
    const std::vector<std::vector<Fruit>>& fruittable,
    const std::vector<std::vector<Item>>& Itemtable,
    std::vector<Fruit>& fruits,
    std::vector<Item>& inventory
) {
    int fruitver = drop(RNG);
    std::uniform_int_distribution<> pickFruitCol(0, fruittable[fruitver].size() - 1);
    int fruitCol = pickFruitCol(RNG);
    fruits.push_back(fruittable[fruitver][fruitCol]);

    int itemRow = item(RNG);
    if (itemRow > 0) {
        std::uniform_int_distribution<> pickItemCol(0, Itemtable[itemRow].size() - 1);
        int itemCol = pickItemCol(RNG);
        inventory.push_back(Itemtable[itemRow][itemCol]);
    }
}

int main() {
    std::random_device rd;
    std::mt19937 RNG(rd());

    std::discrete_distribution<> drop({49.5, 26.0, 10.0, 8.0, 1.0});
    std::discrete_distribution<> item({68.0, 15.0, 5.0, 5.0, 5.0, 2.0});

    std::vector<Fruit> fruits;
    std::vector<Item> inventory;

    std::vector<std::vector<Fruit>> fruittable = {
        { {"Suke suke", 0}, {"Kilo kilo", 0}, {"heal heal", 0}, {"Spin spin", 0} },
        { {"bari bari", 1}, {"mero mero", 1}, {"bomu bomu", 1}, {"gomu gomu", 1}, {"horo horo", 1} },
        { {"bane bane", 2}, {"yomi yomi", 2}, {"kira kira", 2} },
        { {"Bisu bisu", 3}, {"Goro goro", 3}, {"Goru goru", 3}, {"Gura gura", 3}, {"Hie hie", 3}, {"Ito ito", 3}, {"Kage kage", 3}, {"Magu magu", 3}, {"Mera mera", 3}, {"Moku moku", 3}, {"Nikyu nikyu", 3}, {"Pika pika", 3}, {"Suna suna", 3}, {"Yami yami", 3}, {"Yuki yuki", 3}, {"Zushi zushi", 3} },
        { {"Doku doku", 4}, {"Hito hito", 4}, {"Mochi mochi", 4}, {"Neko neko", 4}, {"Ope ope", 4}, {"Ryu ryu", 4}, {"Soru soru", 4}, {"Tori tori", 4}, {"Uo uo", 4} }
    };

    std::vector<std::vector<Item>> Itemtable = {
        { {"No drop", 0} },
        { {"Sp reset", 1} },
        { {"Sp reset", 2}, {"Dark root", 2}, {"Cupid's Headband", 2}, {"Cupid's Mask", 2} },
        { {"Virtuous Cupid Vanguard Outfit", 3}, {"Virtuous Cupid Vanguard Helmet", 3} },
        { {"Leo's Blazing Regalia", 4}, {"Love Boppers Headband", 4}, {"Love Shades", 4}, {"Cupid's Harp", 4}, {"Leo's Blazing Scarf", 5} },
        { {"Cupid's Wand", 5}, {"Cupid's Battleaxe", 5}, {"Virtuous Cupid Queen's Outfit", 5}, {"Virtuous Cupid Queen's Wings", 5}, {"Cupid's Chakram", 5} }
    };

    std::cout << "How many dungeons?\n";
    int runs {0};
    std::cin >> runs;

    for (int i = 0; i < runs; i++) {
        dungeons(RNG, drop, item, fruittable, Itemtable, fruits, inventory);
    }

    std::cout << "\n--- Legendary & Mythical Fruits ---\n";
    for (const Fruit& f : fruits) {
        if (f.rarity >= 3) {
            std::cout << f.name << (f.rarity == 4 ? " [Mythical]" : " [Legendary]") << '\n';
        }
    }

    std::cout << "\n--- Legendary Items ---\n";
    for (const Item& it : inventory) {
        if (it.Itemrarity == 5) {
            std::cout << it.itemName << '\n';
        }
    }

    return 0;
}