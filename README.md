#Mutual Mobile Drawer Controller
`MMDrawerController` is a side drawer navigation container view controller designed to support the growing number of applications that leverage the side drawer paradigm. This library is designed to exclusively support side drawer navigation in a light-weight, focused approach while exposing the ability to provide custom animations for presenting and dismissing the drawer.

`MMDrawerController` 是一个 侧边抽屉导航控制器, 越来越多的应用被设计要支持侧边抽屉导航, 该框架 仅仅支持轻量级的 侧边 抽屉 导航. 提供了多种抽屉展示方式

<p align="center" >
<img src="http://mutualmobile.github.io/MMDrawerController/ExampleImages/example1.png" width="266" height="500"/>
<img src="http://mutualmobile.github.io/MMDrawerController/ExampleImages/example2.png" width="266" height="500"/>
</p>

---
##Documentation
Official appledoc documentation can be found at [CocoaDocs](http://cocoadocs.org/docsets/MMDrawerController/).

文档
正式的 appledoc 文档 可以在 这里找到[CocaDocs](http://cocoadocs.org/docsets/MMDrawerController/).
---
##Installing MMDrawerController
<img src="https://cocoapod-badges.herokuapp.com/v/MMDrawerController/badge.png"/><br/>
You can install MMDrawerController in your project by using [CocoaPods](https://github.com/cocoapods/cocoapods):

## 使用 MMDrawerController
你可以通过 CocoaPods 把 MMDrawerController 集成到我们的项目中

```Ruby
pod 'MMDrawerController', '~> 0.5.7'
```

---
##Creating a Drawer Controller
Creating a `MMDrawerController` is as easy as creating a center view controller and the drawer view controllers, and init'ing the drawer.

创建 `MMDrawerController` 很容易, 一个 中间 的 viewController  一个 抽屉 就可以了
```Objective-C
UIViewController * leftDrawer = [[UIViewController alloc] init];
UIViewController * center = [[UIViewController alloc] init];
UIViewController * rightDrawer = [[UIViewController alloc] init];

MMDrawerController * drawerController = [[MMDrawerController alloc]
                                  	   initWithCenterViewController:center
										   leftDrawerViewController:leftDrawer
										   rightDrawerViewController:rightDrawer];
```

---
##Features

###UINavigationController Support
`MMDrawerController` seamlessly accepts a `UINavigationController` as the `centerViewController`, and will update all of the gesture support automatically. In addition, any child view controller contained within the `UINavigationController` will have access to the parent drawer controller using the category explained [below](#accessing-the-drawer-controller-from-a-child-view-controller).

### 支持 UINavigationController
`MMDrawerController` 接受 `UINavigationController`  作为 `centerViewController`, 自动更新手势支持, 除此之外 , 任何被包含在 `UINavigationController` 中的子视图控制器 可以通过分类来获得 它 的抽屉容器 `MMDrawerController`

###UIGestureRecognizer Support
`MMDrawerController` exposes gesture support for opening and closing the drawer through two masks, one for opening and one for closing. The options are as follows:

###手势支持
`MMDrawerController` 支持打开和关闭抽屉的手势 , 下面是关于手势的说明

* **MMOpenDrawerGestureMode**
 * **MMOpenDrawerGestureModePanningNavigationBar**: The user can open the drawer by panning anywhere on the navigation bar.
 * **MMOpenDrawerGestureModePanningCenterView**: The user can open the drawer by panning anywhere on the center view.
 * **MMOpenDrawerGestureModeBezelPanningCenterView**: The user can open the drawer by starting a pan anywhere within 20 points of the bezel.
 * **MMOpenDrawerGestureModeCustom**: The developer can provide a callback block to determine if the gesture should be recognized. More information below.

* **MMCloseDrawerGestureMode**
 * **MMCloseDrawerGestureModePanningNavigationBar**: The user can close the drawer by panning anywhere on the navigation bar.
 * **MMCloseDrawerGestureModePanningCenterView**: The user can close the drawer by panning anywhere on the center view.
 * **MMCloseDrawerGestureModeBezelPanningCenterView**: The user can close the drawer by starting a pan anywhere within the bezel of the center view.
 * **MMCloseDrawerGestureModeTapNavigationBar**: The user can close the drawer by tapping the navigation bar.
 * **MMCloseDrawerGestureModeTapCenterView**: The user can close the drawer by tapping the center view.
 * **MMCloseDrawerGestureModePanningDrawerView**: The user can close the drawer by panning anywhere on the drawer view.
 * **MMCloseDrawerGestureModeCustom**: The developer can provide a callback block to determine if the gesture should be recognized. More information below.
 
 
 
 * **MMOpenDrawerGestureMode** 打开抽屉手势
 * **MMOpenDrawerGestureModePanningNavigationBar**: 滑动导航栏 打开抽屉.
 * **MMOpenDrawerGestureModePanningCenterView**: 滑动中间视图控制器的 view 打开抽屉.
 * **MMOpenDrawerGestureModeBezelPanningCenterView**: 在距离中间控制器视图 左右边框20长度范围内 滑动可以打开抽屉.
 * **MMOpenDrawerGestureModeCustom**: 自定义手势打开 抽屉.

* **MMCloseDrawerGestureMode** 关闭抽屉手势
 * **MMCloseDrawerGestureModePanningNavigationBar**: 滑动导航栏 关闭抽屉.
 * **MMCloseDrawerGestureModePanningCenterView**: 滑动中间视图控制器的 view 关闭抽屉.
 * **MMCloseDrawerGestureModeBezelPanningCenterView**: 在距离中间控制器视图 边框20长度范围内 滑动可以关闭抽屉..
 * **MMCloseDrawerGestureModeTapNavigationBar**: 点击导航栏关闭抽屉.
 * **MMCloseDrawerGestureModeTapCenterView**: 点击中间视图关闭抽屉.
 * **MMCloseDrawerGestureModePanningDrawerView**: 在任何地方滑动 关闭抽屉.
 * **MMCloseDrawerGestureModeCustom**: 自定义关闭抽屉 手势 更多信息 往下看.
 
 
 
You are free to set whatever combination you want for opening and closing. Note that these gestures may impact touches sent to the child view controllers, so be sure to use these appropriately for your application. For example, you wouldn't want `MMOpenDrawerGestureModePanningCenterView` set if a `MKMapView` is your center view controller, since it would intercept the pan meant for moving around the map.

你可以自由的结合打开和关闭手势, 要注意的是, 这些手势有可能会跟容器内的控制器有冲突, 使用时 要确保不会造成手势冲突, 比如, 当你的中间视图是 `MKMapView` 时, 不能设置打开手势 `MMOpenDrawerGestureModePanningCenterView` 因为它会截断地图的移动手势. 地图将无法滑动.

####Custom Gesture Recognizer Support
Starting with version 0.3.0, you can now provide a callback block to determine if a gesture should be recognized using the `setGestureShouldRecognizeTouchBlock:` method. This method provides three parameters - the drawer controller, the gesture, and the touch. As a developer, you are responsible for inspecting those elements and determining if the gesture should be recognized or not. Note the block is only consulted if you have set `MMOpenDrawerGestureModeCustom`/`MMCloseDrawerGestureModeCustom` on the appropriate mask.

For example, lets say you have a center view controller that contains a few elements, and you only want the pan gesture to be recognized to open the drawer when the touch begins within a certain subview. You would make sure that the `openDrawerGestureModeMask` contains `MMOpenDrawerGestureModeCustom`, and you could set a block below as so:

### 自定义手势支持
从 0.3.0版本开始支持 , 你可以使用这个闭包回调 `setGestureShouldRecognizeTouchBlock:` 方法 来决定是否识别手势. 这个方法提供了三个参数, 抽屉控制器, 手势 `gesture`, 触摸事件`touch` 你可以通过这些参数判断 手势是否被识别, 只有你设置了 `MMOpenDrawerGestureModeCustom`/`MMCloseDrawerGestureModeCustom` 这个 `block` 才会生效

比如: 当你的中间控制器 内 有多个元素, 只有你滑动其中一个子元素时 才能打开抽屉, 你要确保 `openDrawerGestureModeMask` 中包含 `MMOpenDrawerGestureModeCustom` 闭包的实现如下:

```Objective-C
[myDrawerController
 setGestureShouldRecognizeTouchBlock:^BOOL(MMDrawerController *drawerController, UIGestureRecognizer *gesture, UITouch *touch) {
 
     // 是否识别手势  
     BOOL shouldRecognizeTouch = NO;
     //判断抽屉有没有打开 是不是滑动手势
     if(drawerController.openSide == MMDrawerSideNone &&
        [gesture isKindOfClass:[UIPanGestureRecognizer class]]){
	//拿到 特定的元素customView
         UIView * customView = [drawerController.centerViewController myCustomSubview];
	 //拿到 手势在customView中的点
         CGPoint location = [touch locationInView:customView];
	 //点location是否在customView范围内
         shouldRecognizeTouch = (CGRectContainsPoint(customView.bounds, location));
     }
     return shouldRecognizeTouch;
 }];
 ```
 
 Note that you would not want the `openDrawerGestureModeMask` to contain `MMOpenDrawerGestureModePanningCenterView`, since that would take over and be applied automatically regardless of where the touch begins within the center view.

注意: 这时 `openDrawerGestureModeMask` 不能包含 `MMOpenDrawerGestureModePanningCenterView` ,因为 这个手势会自动让中间控制器视图所有的元素通过滑动打开抽屉.(我们的要求是只要其中某一个特定的元素才能滑动打开抽屉)


###Custom Drawer Open/Close Animations
`MMDrawerController` provides a callback block that allows you to implement your own custom state for the drawer controller when an open/close or pan gesture event happens. Within the block, you are responsible for updating the visual state of the drawer controller, and the drawer controller will handle animating to that state.

For example, to set the alpha of the side drawer controller from 0 to 1 during an animation, you would do the following:


### 自定义 抽屉打开/关闭 动画
`MMDrawerController` 提供了一个闭包回调 当抽屉打开和关闭时候 可以自定义动画效果, 来跟新抽屉的可见状态
例如: 设置一个抽屉控制器的透明度从 0 到 1 做动画, 可以使用下面的代码

```Objective-C
[drawerController
     setDrawerVisualStateBlock:^(MMDrawerController *drawerController, MMDrawerSide drawerSide, CGFloat percentVisible) {
         UIViewController * sideDrawerViewController;
	 	//坐边抽屉
		 if(drawerSide == MMDrawerSideLeft){
			 sideDrawerViewController = drawerController.leftDrawerViewController;
		 }
		 else if(drawerSide == MMDrawerSideRight){
			 sideDrawerViewController = drawerController.rightDrawerViewController;
		 }
		 //设置 alpha 值 
		 [sideDrawerViewController.view setAlpha:percentVisible];
     }];
```

In addition, `MMDrawerController` ships with several prebuilt animations to let you go crazy right out of the box. These are included as a subspec for the project, and more information can be found [below](#prebuilt-example-animations).

除此之外, 框架提供的一些抽屉动画会让你疯狂, 这些都是项目的补充, 更多信息继续往下看


###Center View Controller Interaction Mode
When a drawer is open, you can control how a user can interact with the center view controller. 

###中间 视图控制器的交互
当抽屉已经打开, 你可以控制中间 viewController 的交互模式

* **MMDrawerOpenCenterInteractionModeNone**: The user can not interact with any content in the center view.
* **MMDrawerOpenCenterInteractionModeFull**: The user can interact with all content in the center view.
* **MMDrawerOpenCenterInteractionModeNavigationBarOnly**: The user can interact with only content on the navigation bar. The setting allows the menu button to still respond, allowing you to toggle the drawer closed when it is open. This is the default setting.

* **MMDrawerOpenCenterInteractionModeNone**: 中间的控制器不会有任何交互
* **MMDrawerOpenCenterInteractionModeFull**: 中间控制器 交互打开
* **MMDrawerOpenCenterInteractionModeNavigationBarOnly**: 仅仅只有中间控制器的 导航栏交互打开, 也就是菜单按钮可以响应, 允许你点击菜单按钮关闭抽屉. 默认设置


###Accessing the Drawer Controller from a Child View Controller
You can use the `UIViewController+MMDrawerController` category in order to query the drawerController directly from child view controllers.

###从子控制器获取抽屉控制器
可以使用 `UIViewController+MMDrawerController` 分类 来查询 子控制器 的 抽屉控制器

###State Restoration
Beginning with 0.4.0, `MMDrawerController` supports iOS state restoration. In order to opt in to state restoration for `MMDrawerController`, you must set the `restorationIdentifier` of your drawer controller. Instances of your `centerViewController`, `leftDrawerViewController` and `rightDrawerViewController` must also be configured with their own `restorationIdentifier` (and optionally a restorationClass) if you intend for those to be restored as well. If your MMDrawerController had an open drawer when your app was sent to the background, that state will also be restored.

### 状态重用
从0.4.0 版本开始 `MMDrawerController` 支持重用状态, 为了选择 `MMDrawerController` 的重用状态, 你必须设置抽屉控制器的 重用标志`restorationIdentifier` , `centerViewController`, `leftDrawerViewController` 和 `rightDrawerViewController`的实例也要设置重用标志, 这样当你的抽屉为打开状态下, 程序进入后台 抽屉的打开状态将会被储存.

##iOS 7 Status Bar Support
###Child View Controller Support
Beginning with iOS 7, the child view controllers will by default determine the state of the status bar, including its' style and whether or not it is hidden. This value will also be updated anytime the open side changes state, meaning that a side drawer can provide a different value than the center view controller.

##iOS 7 状态栏 支持
###iOS7 之后 子控制器开始支持状态栏, 默认情况下, 子视图控制器确定状态栏的情况, 包含状态栏的样式和是否影藏, 状态栏的样式会随着抽屉的开关状态而随这改变,也就是说 抽屉的状态栏可以和中间视图控制器的状态栏不一样

If you do not want the drawer controller to consult the child view controllers for this state, you should subclass `MMDrawerController`, override `childViewControllerForStatusBarStyle` and `childViewControllerForStatusBarHidden`, and return nil for both.

如果你不想抽屉控制器拥有额外的状态栏, 你应该继承 `MMDrawerController` 重写方法 `childViewControllerForStatusBarStyle` and `childViewControllerForStatusBarHidden` 都返回 nil 

###Custom Status Bar Background View
If you have a contrasting colors between your center view controller and your drawer controllers, the new iOS 7 status bar handling could cause your application to look less than ideal. Starting with iOS 7, `MMDrawerController` supports drawing a custom status bar area at the top of the screen, to give you an area to display the status bar with a constant color, while allowing you to draw custom content below the status bar without worrying about the color of your navigation bars or the top of your content running up underneath the status bar. Using the feature essentially mimics <= iOS 6.X behavior. 

To enable a custom status bar, simple set `showsStatusBarBackgroundView` to `YES`. By default, this will draw a black a view underneath the status bar, and adjust your to content to be laid out lower than the status bar. If you would like a custom status background color, you can set `statusBarViewBackgroundColor` to whatever color you desire.


###自定义 状态栏的背景视图
如果你的中间控制器和抽屉控制器 拥有不同的颜色风格, iOS 7 之后的状态栏可能表现的跟你想象的不太一样, iOS 7 之后, `MMDrawerController` 支持抽屉控制器有一个自定义状态栏, 提供给你一个区域去呈现特性颜色的状态栏,允许你在状态栏下绘制自定义内容不用担心 状态栏下面的导航栏的颜色会发生变化(iOS 7 之后 状态栏颜色会影响导航栏颜色 反之亦然) 这里使用了 iOS 6 之前的状态栏行为(iOS 6 之前 导航栏 和 状态栏互不影响, 这里采用了 iOS 6 的设计方式)
---
##Subclassing
If you plan to subclass `MMDrawerController`, import `MMDrawerController+Subclass.h` into your subclass to access protected methods for `MMDrawerController.` Note that several methods assume and require you to call super, so be sure to follow that convention.

If there is specific functionality you need that is not supported by these methods, please open a Github issue explaining your needs and we can try and find a way to open up methods that can help you out.

---
##Bells and Whistles
A few extras to make your life easier...

###MMDrawerBarButtonItem
Using Paint Code, we created a standard Menu Button that you can use in any `UINavigationBar`, and make it whatever color you want. It's included as a subspec to this library. Enjoy.

Starting with iOS 7, the drawer button is now drawn in a much thinner stroke. In addition, the color methods have been deprecated, and the color will now be determined by the `tintColor.` Also note that the shadow has been deprecated to be more in line with the design themes of the OS.

###Prebuilt Example Animations
In order to make it as easy as possible for you to use this library, we built some of the common animations we see out there today. Simply include the `MMDrawerVisualStates` subspec, and use any of the prebuilt visual states.

For example, if you wanted to use a slide and scale animation, you would do the following:

```Objective-C
[drawerController setDrawerVisualStateBlock:[MMDrawerVisualState slideAndScaleVisualStateBlock]];
```

And that's it...

Here's a quick list of the built in animations:

* **Slide**: The drawer slides at the same rate as the center view controller.
* **Slide and Scale**: The drawer slides and scales up at the same time, while also alpha'ing from 0.0 to 1.0.
* **Swinging Door**: The drawer swings in along a hinge on the center view controller.
* **Parallax**: The drawer slides in at a slower rate than the center view controller, giving a parallax effect.

###Stretchy Drawer
By default, the side drawer will stretch if the user pans past the maximum drawer width. This gives a playful stretch effect. You can disable this by setting `shouldStretchDrawer` to NO, or you can make your own overshoot animation by creating a custom visual state block and setting up custom transforms for when percentVisible is greater than 1.0

###Bounce Preview
To make your side drawer more discoverable, it may be helpful to bounce the drawer the first time your user launches the app. You can use the `bouncePreviewForDrawerSide:completion:` method to easily do this.

If you would like to bounce a custom distance, you can use `bouncePreviewForDrawerSide:distance:completion:`.

###Nifty Example
We decided to spruce up the example a bit using graphics generated from PaintCode. Hope you like it.

The example shows off all the features of the library. Give it a whirl.

---
##What this Library Doesn't Do
In order to keep this library light-weight, we had to make some design trade off decisions. Specifically, we decided this library would NOT DO the following:

* Top or bottom drawer views
* Displaying both drawers at one time
* Displaying a minimum drawer width
* Support container view controllers other than `UINavigationController` (such as `UITabBarController` or `UISplitViewController`) as the center view controller. 
* Support presenting the drawer above the center view controller (like the Google+ app).

We're sure this list will grow over time. But that's the cost of keeping something maintainable :)

---
##Workarounds/FAQs
####How do I support editing/dragging cells in a tableview in the center view controller?
The best way to support this is to set the open/close mask to `MMOpenDrawerGestureModeNone` / `MMCloseDrawerGestureModeNone` while editing is enabled, and restore the mask when editing is finished. This will allow the proper gestures/touches to be passed all the way to the table view. ([#184](https://github.com/mutualmobile/MMDrawerController/issues/184))


---
##Credit
Designed and Developed by these fine folks at [Mutual Mobile](http://mutualmobile.com):

###Development

* [Kevin Harwood](http://twitter.com/kevinharwood)
* [Lars Anderson](http://twitter.com/theonlylars)
* [Rene Cacheaux](http://twitter.com/rcachatx)
* [Conrad Stoll](http://twitter.com/conradstoll)

###Design

* [Matt McDaniel](http://twitter.com/supermattzor)

---
##Feedback
We'd love to hear feedback on the library. Create Github issues, or hit us up on Twitter.

---
##License
`MMDrawerController` is available under the MIT license. See the LICENSE file for more info.
