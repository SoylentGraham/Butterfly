#pragma once

#include "Main.h"
#include "ofxUi.h"
#include "BLondon.h"





class BPanel;

class BRender
{
public:
	BRender(BLondon& London);
	~BRender();

	void			Render();

public:
	BLondon&		mLondon;

	Array<BPanel*>	mPanels;
	ofColor			mBackgroundColour;
};


//----------------------------------
//	panel generator
//----------------------------------
class BPanel
{
public:
	BPanel();
	virtual ~BPanel();

protected:
	virtual void	OnButtonDown(const char* ButtonName)		{	}
	virtual void	OnButtonUp(const char* ButtonName)		{	}

	void			OnGuiEvent(ofxUIEventArgs &e);

public:
	ofxUIScrollableCanvas*	mGui;
};



//	panel of controls
template<typename ENUM>
class BButtonPanel : public BPanel
{
public:
	typedef ENUM Type;

public:
	BButtonPanel(const char* Title=NULL);

protected:
	virtual void		OnButtonDown(const char* ButtonName);
	virtual void		OnButtonDown(ENUM Button)			{	}
	virtual void		OnButtonUp(const char* ButtonName);
	virtual void		OnButtonUp(ENUM Button)			{	}
};



class BLondonPanel : public BButtonPanel<BLondonCommand::Type>
{
public:
	BLondonPanel(BLondon& London);

	void				OnUpdate(ofEventArgs &data);
	virtual void		OnButtonDown(BLondonCommand::Type Button);

protected:
	BLondon&		mLondon;
	ofxUILabel*		mTimeLabel;
};




template<typename ENUM>
BButtonPanel<ENUM>::BButtonPanel(const char* Title)
{
	ofVec2f ButtonSize( 32, 32 );

	//	add panel title
	if ( !Title )
		Title = SoyEnum::GetName<ENUM>();
	mGui->addWidgetDown(new ofxUILabel( Title, OFX_UI_FONT_LARGE)); 

	//	add buttons	
	BufferArray<ENUM,100> Types;
	SoyEnum::GetArray( GetArrayBridge(Types) );
	for ( int i=0;	i<Types.GetSize();	i++ )
	{
		auto EnumString = SoyEnum::ToString(Types[i]);
		auto* pButton = new ofxUIButton( static_cast<const char*>(EnumString), false, ButtonSize.x, ButtonSize.y );
	    mGui->addWidgetDown( pButton );
	}

	//	resize
	mGui->autoSizeToFitWidgets();
};


template<typename ENUM>
void BButtonPanel<ENUM>::OnButtonDown(const char* ButtonName)
{
	BufferArray<ENUM,10> Types;
	SoyEnum::GetArray( GetArrayBridge(Types) );
	for ( int i=0;	i<Types.GetSize();	i++ )
	{
		ENUM Enum = Types[i];
		auto EnumName = SoyEnum::ToString( Enum );
		if ( EnumName == ButtonName )
			OnButtonDown( Enum );
	}
}


template<typename ENUM>
void BButtonPanel<ENUM>::OnButtonUp(const char* ButtonName)
{
	BufferArray<ENUM,10> Types;
	SoyEnum::GetArray( GetArrayBridge(Types) );
	for ( int i=0;	i<Types.GetSize();	i++ )
	{
		ENUM Enum = Types[i];
		auto EnumName = SoyEnum::ToString( Enum );
		if ( EnumName == ButtonName )
			OnButtonUp( Enum );
	}
}

