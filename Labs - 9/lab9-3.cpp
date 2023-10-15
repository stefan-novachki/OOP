// Lab 10 - 1

#include<iostream>
#include<cstring>

using namespace std;

class UserAlreadyExistsException {
private:
    char username[50];
public:
    UserAlreadyExistsException(char *username) {
        strcpy(this->username, username);
    }

    void showMessage() {
        cout << "User with username " << username << " already exists!" << endl;
    }
};

class UserNotFoundException {
private:
    char username[50];
public:
    UserNotFoundException(char *username) {
        strcpy(this->username, username);
    }

    void showMessage() {
        cout << "User with username " << username << " was not found!" << endl;
    }
};

class FriendsLimitExceededException {
private:
    int friends;
public:
    FriendsLimitExceededException(int friends) : friends(friends) {}

    void showMessage() {
        cout << "Can't have more than " << friends << " friends." << endl;
    }
};

class User {
private:
    char username[50];
    int age;
    int friends;
    static int MAX_FRIENDS;
public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
        if (friends == MAX_FRIENDS) {
            throw FriendsLimitExceededException(MAX_FRIENDS);
        }
        ++friends;
        return *this;
    }

    friend class SocialNetwork;

    static void setLimit(int l) {
        MAX_FRIENDS = l;
    }
};

int User::MAX_FRIENDS = 3;

class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, u.username) == 0) {
                throw UserAlreadyExistsException(users[i].username);
            }
        }

        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        try {
                            ++users[i];
                            try {
                                ++users[j];
                            } catch (FriendsLimitExceededException &e) {
                                e.showMessage();
                                users[i].friends--;
                            }
                        } catch (FriendsLimitExceededException &e) {
                            e.showMessage();
                        }

                        return;
                    }
                }

                throw UserNotFoundException(secondUsername);
            }
        }
        throw UserNotFoundException(secondUsername);
    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i = 0; i < network.n; i++) {
            os << network.users[i] << endl;
        }
        return os;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char username[50];
        int age;
        cin >> username >> age;
        User u(username, age);
        try {
            sn += u;
        } catch (UserAlreadyExistsException &e) {
            e.showMessage();
        }
    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i = 0; i < friendships; i++) {
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        } catch (UserNotFoundException &u) {
            u.showMessage();
        } catch (FriendsLimitExceededException &e) {
            e.showMessage();
        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i = 0; i < friendships; i++) {
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        } catch (UserNotFoundException &u) {
            u.showMessage();
        }
    }
    cout << sn;
    return 0;
}
