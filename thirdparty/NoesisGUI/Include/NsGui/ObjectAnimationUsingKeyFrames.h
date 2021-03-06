////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_OBJECTANIMATIONUSINGKEYFRAMES_H__
#define __GUI_OBJECTANIMATIONUSINGKEYFRAMES_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/AnimationTimeline.h>


namespace Noesis
{

class ObjectKeyFrame;
template<class T> class FreezableCollection;
typedef FreezableCollection<ObjectKeyFrame> ObjectKeyFrameCollection;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates the value of a *BaseComponent* property along a set of *KeyFrames*.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.objectanimationusingkeyframes.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API ObjectAnimationUsingKeyFrames final: public AnimationTimeline
{
public:
    ObjectAnimationUsingKeyFrames();
    ~ObjectAnimationUsingKeyFrames();

    /// Gets the type of value this animation generates
    const Type* GetTargetPropertyType() const override;

    /// Gets the collection of KeyFrame objects that define the animation
    ObjectKeyFrameCollection* GetKeyFrames() const;

    // Hides Freezable methods for convenience
    //@{
    Ptr<ObjectAnimationUsingKeyFrames> Clone() const;
    Ptr<ObjectAnimationUsingKeyFrames> CloneCurrentValue() const;
    //@}

    /// From AnimationTimeline
    //@{
    Ptr<BaseComponent> GetAnimatedValue(BaseComponent* defaultOrigin,
        BaseComponent* defaultDestination, AnimationClock* clock) override;
    //@}

private:
    /// From DependencyObject
    //@{
    void OnInit() override;
    //@}

    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source) override;
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

    /// From Timeline
    //@{
    Duration GetNaturalDuration(Clock* clock) const override;
    Duration GetEffectiveDuration() const override;
    //@}

    /// From AnimationTimeline
    //@{
    Ptr<AnimationTimeline> CreateTransitionFrom() const override;
    Ptr<AnimationTimeline> CreateTransitionTo() const override;
    //@}

private:
    mutable Ptr<ObjectKeyFrameCollection> mKeyFrames;
    Vector<Pair<Ptr<ObjectKeyFrame>, double>> mOrderedFrames;
    mutable Duration mNaturalDuration;

    NS_DECLARE_REFLECTION(ObjectAnimationUsingKeyFrames, AnimationTimeline)
};

NS_WARNING_POP

}


#endif
