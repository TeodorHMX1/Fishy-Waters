#pragma once

#include <SFML/Graphics.hpp>
#include "../../../game/src/header/App.h"
#include "../header/FontManager.h"

using namespace sf;

class LevelButton : public Shape
{

public:
    ~LevelButton()
    {

    }

    explicit LevelButton(const Vector2f &size = Vector2f(0, 0))
    {
        mySize = size;
        color = Color::Black;
        hoverColor = Color::Black;
        activeColor = Color::Black;

        font = FontManager().loadFont();

        text.setFont(font);
        text.setFillColor(Color(0, 0, 0, 120));

        update();
    }

public:
    virtual size_t getPointCount() const
    {
        return 4;
    }

    virtual Vector2f getPoint(size_t index) const
    {
        switch (index)
        {
            default:
            case 0:
                return Vector2f(0, 0);
            case 1:
                return Vector2f(mySize.x, 0);
            case 2:
                return Vector2f(mySize.x, mySize.y);
            case 3:
                return Vector2f(0, mySize.y);
        }
    }

    void setSize(const Vector2f &size)
    {
        mySize = size;
        setOrigin(mySize.x / 2, mySize.y / 2);
        update();
    }


    void setColor(Color newColor)
    {
        color = newColor;
    }

    void setHoverColor(Color newHoverColor)
    {
        hoverColor = newHoverColor;
    }

    void setActiveColor(Color newActiveColor)
    {
        activeColor = newActiveColor;
    }

    bool isClicked(RenderWindow &window)
    {
        btnBounders = IntRect(getPosition().x - getGlobalBounds().width / 2,
                              getPosition().y - getGlobalBounds().height / 2,
                              (int) getGlobalBounds().width,
                              (int) getGlobalBounds().height);
        if (btnBounders.contains(Mouse::getPosition(window)))
        {
            this->text.setCharacterSize(characterSize - 2);
            this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);

            bool clicked;
            if (this->mApp == nullptr)
            {
                clicked = false;
            } else
            {
                Event event = this->mApp->getEvent();
                clicked = (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left);
            }
            if (clicked)
            {
                setFillColor(activeColor);
            } else
            {
                setFillColor(hoverColor);
            }
            Sprite mCharacter = mApp->getCharacterSprite();
            mCharacter.setScale(-0.5f, 0.5f);
            mCharacter.setPosition(pos.x + 60, pos.y - 180);
            if (level > mApp->getLevelsUnlocked())
            {
                mCharacter.setColor(Color::Red);
            }
            window.draw(mCharacter);
            return clicked;
        } else
        {
            this->text.setCharacterSize(characterSize);
            this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);
            setFillColor(color);
            return false;
        }

    }

    void setText(std::string text)
    {
        this->content = text;
        this->text.setString(content);
        this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);
    }

    void setCharacterSize(int size)
    {
        this->characterSize = size;
        this->text.setCharacterSize(characterSize);
        this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);
    }

    void setBtnPosition(float x, float y)
    {
        this->pos.x = x;
        this->pos.y = y;
        this->setPosition(x, y);
        this->text.setPosition(x, y);
    }

    void drawText(RenderWindow &window)
    {
        window.draw(text);
    }

    void setFont(Font font)
    {
        this->font = font;
    }

    void setApp(App *app)
    {
        this->mApp = app;
    }

    void setLevel(int level)
    {
        this->level = level;
    }

    int getBtnLevel()
    {
        return this->level;
    }

private:
    Vector2f mySize;
    IntRect btnBounders;
    Color color;
    Color hoverColor;
    Color activeColor;
    Font font;
    Text text;
    String content;
    int characterSize;
    App *mApp;
    int level;
    Vector2f pos;

};
