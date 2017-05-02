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


#import "MMExampleCenterTableViewController.h"
#import "MMExampleDrawerVisualStateManager.h"
#import "UIViewController+MMDrawerController.h"
#import "MMDrawerBarButtonItem.h"
#import "MMLogoView.h"
#import "MMCenterTableViewCell.h"
#import "MMExampleLeftSideDrawerViewController.h"
#import "MMExampleRightSideDrawerViewController.h"
#import "MMNavigationController.h"

#import <QuartzCore/QuartzCore.h>

typedef NS_ENUM(NSInteger, MMCenterViewControllerSection){
    /// 左边控制器 是否可用
    MMCenterViewControllerSectionLeftViewState,
    /// 左边 控制器可选择的动画效果
    MMCenterViewControllerSectionLeftDrawerAnimation,
    /// 右边 控制器 是否可用
    MMCenterViewControllerSectionRightViewState,
    /// 右边 控制器可选择的动画效果
    MMCenterViewControllerSectionRightDrawerAnimation,
};

@interface MMExampleCenterTableViewController ()

@end

@implementation MMExampleCenterTableViewController

- (id)init
{
    self = [super init];
    if (self) {
        [self setRestorationIdentifier:@"MMExampleCenterControllerRestorationKey"];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStyleGrouped];
    [self.tableView setDelegate:self];
    [self.tableView setDataSource:self];
    [self.view addSubview:self.tableView];
    [self.tableView setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
    
    
    //// 双击 弹跳 出 左边 抽屉 40 点 的距离 然后 再 弹 回去
    UITapGestureRecognizer * doubleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap:)];
    [doubleTap setNumberOfTapsRequired:2];
    [self.view addGestureRecognizer:doubleTap];
    
    
    //// 双指 双击 弹出 右边 抽屉 40 点 的距离 然后 再 弹回去
    UITapGestureRecognizer * twoFingerDoubleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(twoFingerDoubleTap:)];
    [twoFingerDoubleTap setNumberOfTapsRequired:2];
    [twoFingerDoubleTap setNumberOfTouchesRequired:2];
    [self.view addGestureRecognizer:twoFingerDoubleTap];
    

    [self setupLeftMenuButton];
    [self setupRightMenuButton];
    
    UIColor * barColor = [UIColor
                          colorWithRed:247.0/255.0
                          green:249.0/255.0
                          blue:250.0/255.0
                          alpha:1.0];
    [self.navigationController.navigationBar setBarTintColor:barColor];
    
    
    MMLogoView * logo = [[MMLogoView alloc] initWithFrame:CGRectMake(0, 0, 29, 31)];
    [self.navigationItem setTitleView:logo];
    [self.navigationController.view.layer setCornerRadius:10.0f];
    
    
    UIView *backView = [[UIView alloc] init];
    [backView setBackgroundColor:[UIColor colorWithRed:208.0/255.0
                                                 green:208.0/255.0
                                                  blue:208.0/255.0
                                                 alpha:1.0]];
    [self.tableView setBackgroundView:backView];
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    NSLog(@"Center will appear");
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    NSLog(@"Center did appear");
}

-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    NSLog(@"Center will disappear");
}

-(void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    NSLog(@"Center did disappear");
}

-(void)setupLeftMenuButton{
    MMDrawerBarButtonItem * leftDrawerButton = [[MMDrawerBarButtonItem alloc] initWithTarget:self action:@selector(leftDrawerButtonPress:)];
    [self.navigationItem setLeftBarButtonItem:leftDrawerButton animated:YES];
}

-(void)setupRightMenuButton{
    MMDrawerBarButtonItem * rightDrawerButton = [[MMDrawerBarButtonItem alloc] initWithTarget:self action:@selector(rightDrawerButtonPress:)];
    [self.navigationItem setRightBarButtonItem:rightDrawerButton animated:YES];
}

-(void)contentSizeDidChange:(NSString *)size{
    [self.tableView reloadData];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 4;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    switch (section) {
        case MMCenterViewControllerSectionLeftDrawerAnimation:
        case MMCenterViewControllerSectionRightDrawerAnimation:
            return 5;
        case MMCenterViewControllerSectionLeftViewState:
        case MMCenterViewControllerSectionRightViewState:
            return 1;
        default:
            return 0;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        
        cell = [[MMCenterTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
        [cell setSelectionStyle:UITableViewCellSelectionStyleGray];
    }
    
    UIColor * selectedColor = [UIColor
                               colorWithRed:1.0/255.0
                               green:15.0/255.0
                               blue:25.0/255.0
                               alpha:1.0];
    UIColor * unselectedColor = [UIColor
                                 colorWithRed:79.0/255.0
                                 green:93.0/255.0
                                 blue:102.0/255.0
                                 alpha:1.0];
    
    switch (indexPath.section) {
        case MMCenterViewControllerSectionLeftDrawerAnimation:
        case MMCenterViewControllerSectionRightDrawerAnimation:{
             MMDrawerAnimationType animationTypeForSection;
            //left  控制器 动画效果
            if(indexPath.section == MMCenterViewControllerSectionLeftDrawerAnimation){
                animationTypeForSection = [[MMExampleDrawerVisualStateManager sharedManager] leftDrawerAnimationType];
            }
            //right 控制器 动画效果
            else {
                animationTypeForSection = [[MMExampleDrawerVisualStateManager sharedManager] rightDrawerAnimationType];
            }
            
            //right and  left 此时的动画效果 cell 表现形式
            if(animationTypeForSection == indexPath.row){
                [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                [cell.textLabel setTextColor:selectedColor];
            }
            // right and left 可选择的其他动画效果 cell 表现形式
            else {
                [cell setAccessoryType:UITableViewCellAccessoryNone];
                [cell.textLabel setTextColor:unselectedColor];
            }
            //所有动画 名字 在tableview 中的显示
            switch (indexPath.row) {
                case MMDrawerAnimationTypeNone:
                    [cell.textLabel setText:@"None"];
                    break;
                case MMDrawerAnimationTypeSlide:
                    [cell.textLabel setText:@"Slide"];
                    break;
                case MMDrawerAnimationTypeSlideAndScale:
                    [cell.textLabel setText:@"Slide and Scale"];
                    break;
                case MMDrawerAnimationTypeSwingingDoor:
                    [cell.textLabel setText:@"Swinging Door"];
                    break;
                case MMDrawerAnimationTypeParallax:
                    [cell.textLabel setText:@"Parallax"];
                    break;
                default:
                    break;
            }
             break;   
        }
        case MMCenterViewControllerSectionLeftViewState:{
            [cell.textLabel setText:@"Enabled"];
            //是否有 left 控制器
            if(self.mm_drawerController.leftDrawerViewController){
                [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                [cell.textLabel setTextColor:selectedColor];
            }
            else{
                [cell setAccessoryType:UITableViewCellAccessoryNone];
                [cell.textLabel setTextColor:unselectedColor];
            }
            break;
        }
        case MMCenterViewControllerSectionRightViewState:{
            [cell.textLabel setText:@"Enabled"];
            //是否 有 right 控制器
            if(self.mm_drawerController.rightDrawerViewController){
                [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                [cell.textLabel setTextColor:selectedColor];
            }
            else{
                [cell setAccessoryType:UITableViewCellAccessoryNone];
                [cell.textLabel setTextColor:unselectedColor];
            }
            break;
        }
        default:
            break;
    }
    
    return cell;
}

-(NSString*)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section{
    // tableview sectionHeader 标题
    switch (section) {
        case MMCenterViewControllerSectionLeftDrawerAnimation:
            return @"Left Drawer Animation";
        case MMCenterViewControllerSectionRightDrawerAnimation:
            return @"Right Drawer Animation";
        case MMCenterViewControllerSectionLeftViewState:
            return @"Left Drawer";
        case MMCenterViewControllerSectionRightViewState:
            return @"Right Drawer";
        default:
            return nil;
    }
}
#pragma mark - Table view delegate
/// 点击cell 事件
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.section) {
            
            //动画效果选择
        case MMCenterViewControllerSectionLeftDrawerAnimation:
        case MMCenterViewControllerSectionRightDrawerAnimation:{
            if(indexPath.section == MMCenterViewControllerSectionLeftDrawerAnimation){
                [[MMExampleDrawerVisualStateManager sharedManager] setLeftDrawerAnimationType:indexPath.row];
            }
            else {
                [[MMExampleDrawerVisualStateManager sharedManager] setRightDrawerAnimationType:indexPath.row];
            }
            //刷新 section
            [tableView reloadSections:[NSIndexSet indexSetWithIndex:indexPath.section] withRowAnimation:UITableViewRowAnimationNone];
            //代码的方式选中 cell
            [tableView selectRowAtIndexPath:indexPath animated:NO scrollPosition:UITableViewScrollPositionNone];
            //反选效果
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            break;
        }
            //左右 控制器 是否显示
        case MMCenterViewControllerSectionLeftViewState:
        case MMCenterViewControllerSectionRightViewState:{
            UIViewController * sideDrawerViewController;
            MMDrawerSide drawerSide = MMDrawerSideNone;
            if(indexPath.section == MMCenterViewControllerSectionLeftViewState){
                //左边抽屉
                sideDrawerViewController = self.mm_drawerController.leftDrawerViewController;
                drawerSide = MMDrawerSideLeft;
            }
            else if(indexPath.section == MMCenterViewControllerSectionRightViewState){
                //右边抽屉
                sideDrawerViewController = self.mm_drawerController.rightDrawerViewController;
                drawerSide = MMDrawerSideRight;
            }
            
            if(sideDrawerViewController){
                [self.mm_drawerController
                 closeDrawerAnimated:YES
                 completion:^(BOOL finished) {
                     if(drawerSide == MMDrawerSideLeft){
                         //左边抽屉 置 nil
                         [self.mm_drawerController setLeftDrawerViewController:nil];
                         //导航栏 左边 按钮 置 nil
                         [self.navigationItem setLeftBarButtonItems:nil animated:YES];
                     }
                     else if(drawerSide == MMDrawerSideRight){
                         //右边抽屉 置 nil
                         [self.mm_drawerController setRightDrawerViewController:nil];
                         //导航栏 右边 按钮 置 nil
                         [self.navigationItem setRightBarButtonItem:nil animated:YES];
                     }
                     
                     /// 刷新 cell
                     [tableView reloadRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationNone];
                     /// cell 选中效果
                     [tableView selectRowAtIndexPath:indexPath animated:NO scrollPosition:UITableViewScrollPositionNone];
                     /// 反选 效果
                     [tableView deselectRowAtIndexPath:indexPath animated:YES];
                 }];

            }
            else {
                if(drawerSide == MMDrawerSideLeft){
                    /// 添加 左边 抽屉控制器
                    UIViewController * vc = [[MMExampleLeftSideDrawerViewController alloc] init];
                    UINavigationController * navC = [[MMNavigationController alloc] initWithRootViewController:vc];
                    [self.mm_drawerController setLeftDrawerViewController:navC];
                    [self setupLeftMenuButton];
                    
                }
                else if(drawerSide == MMDrawerSideRight){
                    /// 添加 右边 控制器
                    UIViewController * vc = [[MMExampleRightSideDrawerViewController alloc] init];
                    UINavigationController * navC = [[MMNavigationController alloc] initWithRootViewController:vc];
                    [self.mm_drawerController setRightDrawerViewController:navC];
                    [self setupRightMenuButton];
                }
                
                /// 刷新 cell
                [tableView reloadRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationNone];
                /// 代码 选择 cell 效果
                [tableView selectRowAtIndexPath:indexPath animated:NO scrollPosition:UITableViewScrollPositionNone];
                /// 反选择 效果
                [tableView deselectRowAtIndexPath:indexPath animated:YES];
            }
            
            break;
        }
        default:
            break;
    }
}

#pragma mark - Button Handlers 按钮事件

//切换 到 左边 抽屉
-(void)leftDrawerButtonPress:(id)sender{
    [self.mm_drawerController toggleDrawerSide:MMDrawerSideLeft animated:YES completion:nil];
}
// 切换到 右边抽屉
-(void)rightDrawerButtonPress:(id)sender{
    [self.mm_drawerController toggleDrawerSide:MMDrawerSideRight animated:YES completion:nil];
}

// 双击 弹跳 出 左边 抽屉 40 点 的距离 然后 再 弹 回去
-(void)doubleTap:(UITapGestureRecognizer*)gesture{
    [self.mm_drawerController bouncePreviewForDrawerSide:MMDrawerSideLeft completion:nil];
}

// 双指 双击 弹出 右边 抽屉 40 点 的距离 然后 再 弹回去
-(void)twoFingerDoubleTap:(UITapGestureRecognizer*)gesture{
    [self.mm_drawerController bouncePreviewForDrawerSide:MMDrawerSideRight completion:nil];
}

@end
