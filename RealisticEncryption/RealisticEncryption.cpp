#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

class RealisticEncryption {
private:
    std::unordered_map<char, std::string> encryptionMap;
    std::unordered_map<std::string, char> decryptionMap;
    std::vector<std::string> dictionary = {
        "new", "im", "patrick", "developer", "super", "shop", "apple", "banana", "cat", "dog",
        "elephant", "fish", "grape", "house", "ice", "jungle", "kite", "lemon", "monkey", "night",
        "orange", "piano", "queen", "rabbit", "sun", "tree", "umbrella", "violin", "water", "xylophone",
        "yellow", "zebra", "ant", "bird", "cloud", "dolphin", "eagle", "forest", "garden", "hill", "island",
        "jacket", "kangaroo", "lion", "mountain", "nest", "ocean", "penguin", "quilt", "river", "star",
        "tiger", "unicorn", "vase", "whale", "xenon", "yacht", "zoo",
        "avocado", "bicycle", "cactus", "drum", "engine", "flamingo", "guitar", "honey", "igloo", "jelly",
        "koala", "lantern", "mango", "notebook", "octopus", "puzzle", "quasar", "robot", "scooter", "telescope",
        "ukulele", "volcano", "wizard", "xylophone", "yogurt", "zeppelin",
        "airplane", "balloon", "candle", "diamond", "emerald", "feather", "globe", "hammer", "insect", "jewel",
        "kite", "ladder", "mirror", "needle", "ostrich", "peacock", "quiver", "rocket", "sailboat", "tornado",
        "umbrella", "vulture", "waterfall", "x-ray", "yarn", "zeppelin",
        "anchor", "beach", "castle", "desert", "engineer", "fountain", "galaxy", "harbor", "island", "jungle",
        "kayak", "lighthouse", "mountain", "nebula", "orchid", "parrot", "quicksand", "rainbow", "submarine", "treasure",
        "universe", "vortex", "whirlpool", "xenon", "yeti", "zeppelin",
        "asteroid", "bamboo", "comet", "daisy", "emerald", "falcon", "geyser", "horizon", "iceberg", "jungle",
        "koala", "lagoon", "meadow", "nebula", "oasis", "pyramid", "quartz", "reef", "savanna", "tundra",
        "utopia", "valley", "waterfall", "xylophone", "yew", "zenith",
        "amethyst", "blizzard", "coral", "dolphin", "eclipse", "fjord", "glacier", "hurricane", "isthmus", "jungle",
        "kelp", "lava", "magma", "nimbus", "oasis", "prairie", "quagmire", "reef", "savanna", "tundra",
        "underwater", "volcano", "waterfall", "xenon", "yeti", "zenith",
        "asterisk", "barracuda", "carnival", "dandelion", "enchanted", "firefly", "gazebo", "hologram", "illusion", "jigsaw",
        "kaleidoscope", "labyrinth", "marigold", "nebula", "obsidian", "paradise", "quintessence", "rhapsody", "symphony", "tapestry",
        "utensil", "vanguard", "whimsical", "xenophobia", "yonder", "zephyr",
        "alchemy", "basilisk", "crystal", "dragon", "emerald", "fable", "griffin", "hydra", "incantation", "jewel",
        "kraken", "labyrinth", "mermaid", "nymph", "oracle", "phoenix", "quasar", "rune", "sorcery", "talisman",
        "unicorn", "vortex", "werewolf", "xenon", "yeti", "zephyr",
        "astronaut", "barricade", "canyon", "dolphin", "eclipse", "fossil", "gargoyle", "horizon", "illusion", "jungle",
        "kettle", "labyrinth", "meteor", "nebula", "oasis", "pyramid", "quartz", "reef", "sphinx", "tundra",
        "utopia", "vortex", "whirlpool", "xylophone", "yeti", "zenith",
        "aurora", "boulder", "cavern", "dune", "ember", "fjord", "grotto", "hurricane", "isthmus", "jungle",
        "kelp", "lagoon", "mesa", "nimbus", "oasis", "prairie", "quagmire", "reef", "savanna", "tundra",
        "underwater", "volcano", "waterfall", "xenon", "yeti", "zenith",
        "artifact", "banyan", "cascade", "diorama", "ephemeral", "fresco", "galleon", "holograph", "infinity", "jamboree",
        "kale", "lithograph", "mosaic", "nirvana", "obelisk", "panorama", "quintet", "resonance", "silhouette", "trilogy",
        "utensil", "vignette", "whirlwind", "xenolith", "yarn", "zenith"
    };

    std::string key;

    void generateKey() {
        std::srand(std::hash<std::string>{}(key));
        std::vector<std::string> usedWords;
        std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~!@#$%^&*()_+-={}[]|\\:\";'<>?,./";
        for (char c : characters) {
            std::string word;
            do {
                word = dictionary[std::rand() % dictionary.size()];
            } while (std::find(usedWords.begin(), usedWords.end(), word) != usedWords.end());
            usedWords.push_back(word);
            encryptionMap[c] = word;
            decryptionMap[word] = c;
        }
    }

public:
    RealisticEncryption(const std::string& userKey) : key(userKey) {
        generateKey();
        srand(static_cast<unsigned int>(time(0)));
    }

    std::string encrypt(const std::string& input) {
        std::stringstream ss;
        for (char c : input) {
            if (c == ' ') {
                ss << "space ";
            }
            else if (encryptionMap.find(c) != encryptionMap.end()) {
                ss << encryptionMap[c] << " ";
            }
            else {
                ss << c << " ";
            }
        }
        return ss.str();
    }

    std::string decrypt(const std::string& input) {
        std::stringstream ss(input);
        std::string word, result;
        while (ss >> word) {
            std::string lowerWord = word;
            for (char& c : lowerWord) {
                c = tolower(c);
            }
            if (lowerWord == "space") {
                result += ' ';
            }
            else if (decryptionMap.find(lowerWord) != decryptionMap.end()) {
                result += decryptionMap[lowerWord];
            }
            else {
                result += word;
            }
        }
        return result;
    }
};

int main() {
    std::string userKey;
    std::cout << "Enter encryption key: ";
    std::cin >> userKey;

    RealisticEncryption re(userKey);

    std::string message;
    std::cout << "Enter message to encrypt: ";
    std::cin.ignore();
    std::getline(std::cin, message);

    std::string encrypted = re.encrypt(message);
    std::string decrypted = re.decrypt(encrypted);

    std::cout << "Original: " << message << std::endl;
    std::cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
