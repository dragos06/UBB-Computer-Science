#pragma once
#include <string>

class Tutorial
{
private:
	std::string title, presenter, link;
	int duration, likes;
public:

	Tutorial();

	//<summary>Default constructor</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<param name="duration">The duration of the tutorial</param>
	//<param name="likes">The likes of the tutorial</param>
	//<param name="link">The link of the tutorial</param>
	//<returns>The tutorial object</returns>

	Tutorial(std::string title, std::string presenter, int duration, int likes, std::string link);
	
	//<summary>Copy constructor</summary>
	//<param name="tutorial">The tutorial object to be copied</param>
	//<returns>The copied tutorial object</returns>
	Tutorial(const Tutorial& tutorial);
	//~Tutorial();

	//<summary>Getter for the title of the tutorial</summary>
	//<returns>The title of the tutorial</returns>
	std::string getTitle() const;
	
	//<summary>Getter for the presenter of the tutorial</summary>
	//<returns>The presenter of the tutorial</returns>
	std::string getPresenter() const;

	//<summary>Getter for the duration of the tutorial</summary>
	//<returns>The duration of the tutorial</returns>
	int getDuration() const;
	
	//<summary>Getter for the likes of the tutorial</summary>
	//<returns>The likes of the tutorial</returns>
	int getLikes() const;

	//<summary>Getter for the link of the tutorial</summary>
	//<returns>The link of the tutorial</returns>
	std::string getLink() const;

	//<summary>Operator overload for the equality operator</summary>
	//<param name="tutorial">The tutorial object to be compared with</param>
	//<returns>True if the tutorials are equal, false otherwise</returns>
	bool operator==(const Tutorial& tutorial);

	//<summary>Setter for the title of the tutorial</summary>
	//<param name="title">The title of the tutorial</param>
	void setTitle(const std::string& title);

	//<summary>Setter for the presenter of the tutorial</summary>
	//<param name="presenter">The presenter of the tutorial</param>
	void setPresenter(const std::string& presenter);

	//<summary>Setter for the duration of the tutorial</summary>
	//<param name="duration">The duration of the tutorial</param>
	void setDuration(int duration);

	//<summary>Setter for the likes of the tutorial</summary>
	//<param name="likes">The likes of the tutorial</param>
	void setLikes(int likes);

	//<summary>Setter for the link of the tutorial</summary>
	//<param name="link">The link of the tutorial</param>
	void setLink(const std::string& link);

	//<summary>Prints the tutorial</summary>
	void printTutorial();
};