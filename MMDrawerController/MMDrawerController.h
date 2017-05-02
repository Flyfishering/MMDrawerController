// Copyright (c) 2013 Mutual Mobile (http://mutualmobile.com/)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#import <UIKit/UIKit.h>

/**
 `MMDrawerController` is a side drawer navigation container view controller designed to support the growing number of applications that leverage the side drawer paradigm. This library is designed to exclusively support side drawer navigation in light-weight, focused approach.
 这是一个抽屉导航控制器, 越来越多的应用开始使用抽屉效果, 这个库是 轻量级的 抽屉导航控制器
 
 ## Creating a MMDrawerController
 `MMDrawerController` is a container view controller, similiar to `UINavigationController` or `UITabBarController`, with up to three child view controllers - Center, LeftDrawer, and RightDrawer. To create a `MMDrawerController`, you must first instantiate the drawer view controllers and the initial center controller, then call one of the init methods listed in this class.
 
 创建 MMDrawerController
 MMDrawerController 是一个 容器 控制器(和 UINavigationController 或者 UITabBarController 相似) 拥有三个自控制器, 中部, 左边抽屉, 右边抽屉 
    创建 MMDrawerController 前 必须 先创建 上面提到的三个自控制器(左中右), 然后调用 下面给出的初始化方法 来创建

 ## Handling a UINavigationController as the centerViewController
 `MMDrawerController` automatically supports handling a `UINavigationController` as the `centerViewController`, and will correctly handle the proper gestures on each view (the navigation bar view as well as the content view for the visible view controller). Note that while this library does support other container view controllers, the open/close gestures are not customized to support them.
 
 UINavigationController 可以作为 中部 的子控制器
 MMDrawerController 自动支持 UINavigationController 作为 中部 自控制器, 可以正确管理view上的手势(无论是navigation bar view 还是 viewController 的view).
    这个库 也支持包含 其他控制器容器, 这时 手势开关 不接受定制
 
 ## Accessing MMDrawerController from the Child View Controller
 You can leverage the category class (UIViewController+MMDrawerController) included with this library to access information about the parent `MMDrawerController`. Note that if you are contained within a UINavigationController, the `drawerContainerViewController` will still return the proper reference to the `drawerContainerViewController` parent, even though it is not the direct parent. Refer to the documentation included with the category for more information.
 从 子控制器 获取 MMDrawerController
    自控制器 可以通过 分类(UIViewController+MMDrawerController) 来 获取关于 容器 MMDrawerController 的信息
    即使 子控制器 包含在 UINavigationController 中, 在这个库中 自控制器的 容器 默认是 MMDrawerController .
    更多 关于 这个分类的信息, 去分类中查看
 
 ## How MMDrawerOpenCenterInteractionMode is handled
 `MMDrawerOpenCenterInteractionMode` controls how the user should be able to interact with the center view controller when either drawer is open. By default, this is set to `MMDrawerOpenCenterInteractionModeNavigationBarOnly`, which allows the user to interact with UINavigationBarItems while either drawer is open (typicaly used to click the menu button to close). If you set the interaction mode to `MMDrawerOpenCenterInteractionModeNone`, no items within the center view will be able to be interacted with while a drawer is open. Note that this setting has no effect at all on the `MMCloseDrawerGestureMode`.
 MMDrawerOpenCenterInteractionMode 控制了 当抽屉打开时 用户和中部控制器交互的模式. 默认是 MMDrawerOpenCenterInteractionModeNavigationBarOnly 只允许 中部控制器的导航栏可以交互,
     MMDrawerOpenCenterInteractionModeNone: 禁止用户和中部控制器有任何交互
     MMDrawerOpenCenterInteractionModeFull: 用户可以和中部控制器任何地方交互
    注意: 无论设置什么模式, 都不会影响 单击中部控制器 的 手势 去关闭抽屉(MMCloseDrawerGestureMode)
 
 
 ## How Open/Close Gestures are handled
 Two gestures are added to every instance of a drawer controller, one for pan and one for touch. `MMDrawerController` is the delegate for each of the gesture recoginzers, and determines if a touch should be sent to the appropriate gesture when a touch is detected compared with the masks set for open and close gestures and the state of the drawer controller.
 
 打开和关闭 抽屉的手势
    每个抽屉实例都被添加了 两个手势, 拖动手势 和 单击手势,
    MMDrawerController 识别这些手势,
    根据打开和关闭手势的识别 和 抽屉控制器的当前状态, 来决定 这个手势 是否 传递下去
 
 ## Integrating with State Restoration
 In order to opt in to state restoration for `MMDrawerController`, you must set the `restorationIdentifier` of your drawer controller. Instances of your centerViewController, leftDrawerViewController and rightDrawerViewController must also be configured with their own `restorationIdentifier` (and optionally a restorationClass) if you intend for those to be restored as well. If your MMDrawerController had an open drawer when your app was sent to the background, that state will also be restored.
 启用 重用标志
    为了 恢复 MMDrawerController ,你必须给 中部控制器,左边抽屉,右边抽屉 和 MMDrawerController 设置重用标志restorationIdentifier, 这样, 你的应用在 进入后台 或者下次启动时 会 存储 抽屉的打开状态.
 
 ## What this library doesn't do.
 This library is not meant for:
    - Top or bottom drawer views
    - Displaying both drawers at one time
    - Displaying a minimum drawer width
    - Support container view controllers other than `UINavigationController` as the center view controller. 
 
 这个库 不支持 下面的操作
    - 1.不支持 顶部 或者 底部 抽屉
    - 2.不支持 同时 打开 左右 抽屉
    - 3.不支持 显示最小抽屉宽度(没看懂)
    - 4.不支持 将容器控制器设置为 中部控制器 (UINavigationController 除外)
 */

/// 抽屉类型
typedef NS_ENUM(NSInteger,MMDrawerSide){
    /// 不属于任何抽屉类型
    MMDrawerSideNone = 0,
    /// 左边 抽屉类型
    MMDrawerSideLeft,
    /// 右边 抽屉类型
    MMDrawerSideRight,
};

typedef NS_OPTIONS(NSInteger, MMOpenDrawerGestureMode) {
    MMOpenDrawerGestureModeNone                     = 0,
    MMOpenDrawerGestureModePanningNavigationBar     = 1 << 1,
    MMOpenDrawerGestureModePanningCenterView        = 1 << 2,
    MMOpenDrawerGestureModeBezelPanningCenterView   = 1 << 3,
    MMOpenDrawerGestureModeCustom                   = 1 << 4,
    MMOpenDrawerGestureModeAll                      =   MMOpenDrawerGestureModePanningNavigationBar     |
                                                        MMOpenDrawerGestureModePanningCenterView        |
                                                        MMOpenDrawerGestureModeBezelPanningCenterView   |
                                                        MMOpenDrawerGestureModeCustom,
};

typedef NS_OPTIONS(NSInteger, MMCloseDrawerGestureMode) {
    MMCloseDrawerGestureModeNone                    = 0,
    MMCloseDrawerGestureModePanningNavigationBar    = 1 << 1,
    MMCloseDrawerGestureModePanningCenterView       = 1 << 2,
    MMCloseDrawerGestureModeBezelPanningCenterView  = 1 << 3,
    MMCloseDrawerGestureModeTapNavigationBar        = 1 << 4,
    MMCloseDrawerGestureModeTapCenterView           = 1 << 5,
    MMCloseDrawerGestureModePanningDrawerView       = 1 << 6,
    MMCloseDrawerGestureModeCustom                  = 1 << 7,
    MMCloseDrawerGestureModeAll                     =   MMCloseDrawerGestureModePanningNavigationBar    |
                                                        MMCloseDrawerGestureModePanningCenterView       |
                                                        MMCloseDrawerGestureModeBezelPanningCenterView  |
                                                        MMCloseDrawerGestureModeTapNavigationBar        |
                                                        MMCloseDrawerGestureModeTapCenterView           |
                                                        MMCloseDrawerGestureModePanningDrawerView       |
                                                        MMCloseDrawerGestureModeCustom,
};

typedef NS_ENUM(NSInteger, MMDrawerOpenCenterInteractionMode) {
    MMDrawerOpenCenterInteractionModeNone,
    MMDrawerOpenCenterInteractionModeFull,
    MMDrawerOpenCenterInteractionModeNavigationBarOnly,
};

@class  MMDrawerController;
typedef void (^MMDrawerControllerDrawerVisualStateBlock)(MMDrawerController * drawerController, MMDrawerSide drawerSide, CGFloat percentVisible);

@interface MMDrawerController : UIViewController

///---------------------------------------
/// @name Accessing Drawer Container View Controller Properties
///---------------------------------------

/**
 The center view controller. 
 
 This can only be set via the init methods, as well as the `setNewCenterViewController:...` methods. The size of this view controller will automatically be set to the size of the drawer container view controller, and it's position is modified from within this class. Do not modify the frame externally.
 */
@property (nonatomic, strong) UIViewController * centerViewController;

/**
 The left drawer view controller. 
 
 The size of this view controller is managed within this class, and is automatically set to the appropriate size based on the `maximumLeftDrawerWidth`. Do not modify the frame externally.
 */
@property (nonatomic, strong) UIViewController * leftDrawerViewController;

/**
 The right drawer view controller. 
 
 The size of this view controller is managed within this class, and is automatically set to the appropriate size based on the `maximumRightDrawerWidth`. Do not modify the frame externally.
 */
@property (nonatomic, strong) UIViewController * rightDrawerViewController;

/**
 The maximum width of the `leftDrawerViewController`. 
 
 By default, this is set to 280. If the `leftDrawerViewController` is nil, this property will return 0.0;
 */
@property (nonatomic, assign) CGFloat maximumLeftDrawerWidth;

/**
 The maximum width of the `rightDrawerViewController`. 
 
 By default, this is set to 280. If the `rightDrawerViewController` is nil, this property will return 0.0;

 */
@property (nonatomic, assign) CGFloat maximumRightDrawerWidth;

/**
 The visible width of the `leftDrawerViewController`. 
 
 Note this value can be greater than `maximumLeftDrawerWidth` during the full close animation when setting a new center view controller;
 当更换 中间控制器时  可以 大于maximumLeftDrawerWidth
 */
@property (nonatomic, assign, readonly) CGFloat visibleLeftDrawerWidth;

/**
 The visible width of the `rightDrawerViewController`. 
 
 Note this value can be greater than `maximumRightDrawerWidth` during the full close animation when setting a new center view controller;
 */
@property (nonatomic, assign, readonly) CGFloat visibleRightDrawerWidth;

/**
 The animation velocity of the open and close methods, measured in points per second.
 
 By default, this is set to 840 points per second (three times the default drawer width), meaning it takes 1/3 of a second for the `centerViewController` to open/close across the default drawer width. Note that there is a minimum .1 second duration for built in animations, to account for small distance animations.
 */
@property (nonatomic, assign) CGFloat animationVelocity;

/** 
 A boolean that determines whether or not the panning gesture will "hard-stop" at the maximum width for a given drawer side.
 
 By default, this value is set to YES. Enabling `shouldStretchDrawer` will give the pan a gradual asymptotic stopping point much like `UIScrollView` behaves. Note that if this value is set to YES, the `drawerVisualStateBlock` can be passed a `percentVisible` greater than 1.0, so be sure to handle that case appropriately.
 */
@property (nonatomic, assign) BOOL shouldStretchDrawer;

/**
 The current open side of the drawer. 
 
 Note this value will change as soon as a pan gesture opens a drawer, or when a open/close animation is finished.
 */
@property (nonatomic, assign, readonly) MMDrawerSide openSide;

/**
 How a user is allowed to open a drawer using gestures. 
 
 By default, this is set to `MMOpenDrawerGestureModeNone`. Note these gestures may affect user interaction with the `centerViewController`, so be sure to use appropriately.
 */
@property (nonatomic, assign) MMOpenDrawerGestureMode openDrawerGestureModeMask;

/**
 How a user is allowed to close a drawer. 
 
 By default, this is set to `MMCloseDrawerGestureModeNone`. Note these gestures may affect user interaction with the `centerViewController`, so be sure to use appropriately.
 */
@property (nonatomic, assign) MMCloseDrawerGestureMode closeDrawerGestureModeMask;

/**
 The value determining if the user can interact with the `centerViewController` when a side drawer is open. 
 
 By default, it is `MMDrawerOpenCenterInteractionModeNavigationBarOnly`, meaning that the user can only interact with the buttons on the `UINavigationBar`, if the center view controller is a `UINavigationController`. Otherwise, the user cannot interact with any other center view controller elements.
 */
@property (nonatomic, assign) MMDrawerOpenCenterInteractionMode centerHiddenInteractionMode;

/**
 The flag determining if a shadow should be drawn off of `centerViewController` when a drawer is open. 
 
 By default, this is set to YES.
 */
@property (nonatomic, assign) BOOL showsShadow;

/**
 The shadow radius of `centerViewController` when a drawer is open.
 
 By default, this is set to 10.0f;
 */
@property (nonatomic, assign) CGFloat shadowRadius;

/**
 The shadow opacity of `centerViewController` when a drawer is open.
 
 By default, this is set to 0.8f;
 */
@property (nonatomic, assign) CGFloat shadowOpacity;

/**
 The shadow offset of `centerViewController` when a drawer is open.
 
 By default, this is set to (0, -3);
 */
@property (nonatomic, assign) CGSize shadowOffset;

/**
 The color of the shadow drawn off of 'centerViewController` when a drawer is open.
 
 By default, this is set to the systme default (opaque black).
 */
@property (nonatomic, strong) UIColor * shadowColor;

/**
 The flag determining if a custom background view should appear beneath the status bar, forcing the child content to be drawn lower than the status bar.
 
 By default, this is set to NO.
 */
@property (nonatomic, assign) BOOL showsStatusBarBackgroundView;

/**
 The color of the status bar background view if `showsStatusBarBackgroundView` is set to YES.
 
 By default, this is set `[UIColor blackColor]`.
 */
@property (nonatomic, strong) UIColor * statusBarViewBackgroundColor;

/**
 The value determining panning range of centerView's bezel if the user can open drawer with 'MMOpenDrawerGestureModeBezelPanningCenterView' or close drawer with 'MMCloseDrawerGestureModeBezelPanningCenterView' .
 
 By default, this is set 20.0f.
 */
@property (nonatomic, assign) CGFloat bezelPanningCenterViewRange;

/**
 The value determining if the user can open or close drawer with panGesture velocity.
 
 By default, this is set 200.0f.
 */
@property (nonatomic, assign) CGFloat panVelocityXAnimationThreshold;

///---------------------------------------
/// @name Initializing a `MMDrawerController`
///---------------------------------------

/**
 Creates and initializes an `MMDrawerController` object with the specified center view controller, left drawer view controller, and right drawer view controller. 
 
 @param centerViewController The center view controller. This argument must not be `nil`.
 @param leftDrawerViewController The left drawer view controller.
 @param rightDrawerViewController The right drawer controller.
 
 @return The newly-initialized drawer container view controller.
 */
-(instancetype)initWithCenterViewController:(UIViewController *)centerViewController leftDrawerViewController:(UIViewController *)leftDrawerViewController rightDrawerViewController:(UIViewController *)rightDrawerViewController;

/**
 Creates and initializes an `MMDrawerController` object with the specified center view controller, left drawer view controller.
 
 @param centerViewController The center view controller. This argument must not be `nil`.
 @param leftDrawerViewController The left drawer view controller.
 
 @return The newly-initialized drawer container view controller.
 */
-(instancetype)initWithCenterViewController:(UIViewController *)centerViewController leftDrawerViewController:(UIViewController *)leftDrawerViewController;

/**
 Creates and initializes an `MMDrawerController` object with the specified center view controller, right drawer view controller.
 
 @param centerViewController The center view controller. This argument must not be `nil`.
 @param rightDrawerViewController The right drawer controller.
 
 @return The newly-initialized drawer container view controller.
 */
-(instancetype)initWithCenterViewController:(UIViewController *)centerViewController rightDrawerViewController:(UIViewController *)rightDrawerViewController;

///---------------------------------------
/// @name Opening and Closing a Drawer
///---------------------------------------

/**
 Toggles(切换) the drawer open/closed based on the `drawer` passed in.
 
 Note that if you attempt to toggle a drawer closed while the other is open, nothing will happen. For example, if you pass in MMDrawerSideLeft, but the right drawer is open, nothing will happen. In addition, the completion block will be called with the finished flag set to NO.
 
 @param drawerSide The `MMDrawerSide` to toggle. This value cannot be `MMDrawerSideNone`.
 @param animated Determines whether the `drawer` should be toggle animated.
 @param completion The block that is called when the toggle is complete, or if no toggle took place at all.
 
 切换抽屉的打开关闭状态(根据抽屉的当前状态来切换)
    注意: 当你切换一个抽屉的状态, 此时另外一个抽屉当前是打开状态, 则 不做任何操作.(既不打开这个抽屉,也不关闭另外一个抽屉). 例如: 右抽屉已经打开, 左抽屉关闭, 此时你要切换左边抽屉的状态, 实际上 什么操作也不做, 除此之外,block中的 flag 参数也被 置为 NO
 @param drawerSide 要切换状态的抽屉 不能为MMDrawerSideNone`.
 @param animated 是否有切换动画
 @param completion 切换完成之后的操作,或者没有切换失败的操作
 */
-(void)toggleDrawerSide:(MMDrawerSide)drawerSide animated:(BOOL)animated completion:(void(^)(BOOL finished))completion;

/**
 Closes the open drawer.
 
 @param animated Determines whether the drawer side should be closed animated
        是否 有 关闭 动画
 @param completion The block that is called when the close is complete
        关闭 抽屉之后的操作
 
 关闭 已经打开的抽屉
 */
-(void)closeDrawerAnimated:(BOOL)animated completion:(void(^)(BOOL finished))completion;

/**
 Opens the `drawer` passed in.
 
 @param drawerSide The `MMDrawerSide` to open. This value cannot be `MMDrawerSideNone`.
 @param animated Determines whether the `drawer` should be open animated.
 @param completion The block that is called when the toggle is open.
 
 */
-(void)openDrawerSide:(MMDrawerSide)drawerSide animated:(BOOL)animated completion:(void(^)(BOOL finished))completion;

///---------------------------------------
/// @name Setting a new Center View Controller
///---------------------------------------

/**
 Sets the new `centerViewController`. 
 
 This sets the view controller and will automatically adjust the frame based on the current state of the drawer controller. If `closeAnimated` is YES, it will immediately change the center view controller, and close the drawer from its current position.
 
 @param centerViewController The new `centerViewController`.
 @param closeAnimated Determines whether the drawer should be closed with an animation.
 @param completion The block called when the animation is finsihed.
 
 */
-(void)setCenterViewController:(UIViewController *)centerViewController withCloseAnimation:(BOOL)closeAnimated completion:(void(^)(BOOL finished))completion;

/**
 Sets the new `centerViewController`. 
 
 This sets the view controller and will automatically adjust the frame based on the current state of the drawer controller. If `closeFullAnimated` is YES, the current center view controller will animate off the screen, the new center view controller will then be set, followed by the drawer closing across the full width of the screen.
 
 @param newCenterViewController The new `centerViewController`.
 @param fullCloseAnimated Determines whether the drawer should be closed with an animation.
 @param completion The block called when the animation is finsihed.
 
 */
-(void)setCenterViewController:(UIViewController *)newCenterViewController withFullCloseAnimation:(BOOL)fullCloseAnimated completion:(void(^)(BOOL finished))completion;

///---------------------------------------
/// @name Animating the Width of a Drawer
///---------------------------------------

/**
 Sets the maximum width of the left drawer view controller. 
 
 If the drawer is open, and `animated` is YES, it will animate the drawer frame as well as adjust the center view controller. If the drawer is not open, this change will take place immediately.
 
 @param width The new width of left drawer view controller. This must be greater than zero.
 @param animated Determines whether the drawer should be adjusted with an animation.
 @param completion The block called when the animation is finished.
 
 */
-(void)setMaximumLeftDrawerWidth:(CGFloat)width animated:(BOOL)animated completion:(void(^)(BOOL finished))completion;

/**
 Sets the maximum width of the right drawer view controller. 
 
 If the drawer is open, and `animated` is YES, it will animate the drawer frame as well as adjust the center view controller. If the drawer is not open, this change will take place immediately.
 
 @param width The new width of right drawer view controller. This must be greater than zero.
 @param animated Determines whether the drawer should be adjusted with an animation.
 @param completion The block called when the animation is finished.
 
 */
-(void)setMaximumRightDrawerWidth:(CGFloat)width animated:(BOOL)animated completion:(void(^)(BOOL finished))completion;

///---------------------------------------
/// @name Previewing a Drawer
///---------------------------------------

/**
 Bounce preview for the specified `drawerSide` a distance of 40 points.
 
 @param drawerSide The drawer to preview. This value cannot be `MMDrawerSideNone`.
 @param completion The block called when the animation is finsihed.
 
 
 弹跳出一个抽屉 view , 弹跳距离 40 点
 
 
 */
-(void)bouncePreviewForDrawerSide:(MMDrawerSide)drawerSide completion:(void(^)(BOOL finished))completion;

/**
 Bounce preview for the specified `drawerSide`.
 
 @param drawerSide The drawer side to preview. This value cannot be `MMDrawerSideNone`.
 @param distance The distance to bounce.
 @param completion The block called when the animation is finsihed.
 
 */
-(void)bouncePreviewForDrawerSide:(MMDrawerSide)drawerSide distance:(CGFloat)distance completion:(void(^)(BOOL finished))completion;

///---------------------------------------
/// @name Custom Drawer Animations
///---------------------------------------

/**
 Sets a callback to be called when a drawer visual state needs to be updated. 
 
 This block is responsible for updating the drawer's view state, and the drawer controller will handle animating to that state from the current state. This block will be called when the drawer is opened or closed, as well when the user is panning the drawer. This block is not responsible for doing animations directly, but instead just updating the state of the properies (such as alpha, anchor point, transform, etc). Note that if `shouldStretchDrawer` is set to YES, it is possible for `percentVisible` to be greater than 1.0. If `shouldStretchDrawer` is set to NO, `percentVisible` will never be greater than 1.0.
 
 Note that when the drawer is finished opening or closing, the side drawer controller view will be reset with the following properies:
 
    - alpha: 1.0
    - transform: CATransform3DIdentity
    - anchorPoint: (0.5,0.5)
 
 @param drawerVisualStateBlock A block object to be called that allows the implementer to update visual state properties on the drawer. `percentVisible` represents the amount of the drawer space that is current visible, with drawer space being defined as the edge of the screen to the maxmimum drawer width. Note that you do have access to the drawerController, which will allow you to update things like the anchor point of the side drawer layer.
 */
-(void)setDrawerVisualStateBlock:(void(^)(MMDrawerController * drawerController, MMDrawerSide drawerSide, CGFloat percentVisible))drawerVisualStateBlock;

///---------------------------------------
/// @name Gesture Completion Handling
///---------------------------------------

/**
 Sets a callback to be called when a gesture has been completed.
 
 This block is called when a gesture action has been completed. You can query the `openSide` of the `drawerController` to determine what the new state of the drawer is.
 
 @param gestureCompletionBlock A block object to be called that allows the implementer be notified when a gesture action has been completed.
 */
-(void)setGestureCompletionBlock:(void(^)(MMDrawerController * drawerController, UIGestureRecognizer * gesture))gestureCompletionBlock;

///---------------------------------------
/// @name Custom Gesture Handler
///---------------------------------------

/**
 Sets a callback to be called to determine if a UIGestureRecognizer should recieve the given UITouch.
 
 This block provides a way to allow a gesture to be recognized with custom logic. For example, you may have a certain part of your view that should accept a pan gesture recognizer to open the drawer, but not another a part. If you return YES, the gesture is recognized and the appropriate action is taken. This provides similar support to how Facebook allows you to pan on the background view of the main table view, but not the content itself. You can inspect the `openSide` property of the `drawerController` to determine the current state of the drawer, and apply the appropriate logic within your block.
 
 Note that either `openDrawerGestureModeMask` must contain `MMOpenDrawerGestureModeCustom`, or `closeDrawerGestureModeMask` must contain `MMCloseDrawerGestureModeCustom` for this block to be consulted.
 
 @param gestureShouldRecognizeTouchBlock A block object to be called to determine if the given `touch` should be recognized by the given gesture.
 */
-(void)setGestureShouldRecognizeTouchBlock:(BOOL(^)(MMDrawerController * drawerController, UIGestureRecognizer * gesture, UITouch * touch))gestureShouldRecognizeTouchBlock;

@end
