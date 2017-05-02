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

#import "MMExampleViewController.h"

@interface MMExampleViewController ()

@end

@implementation MMExampleViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    //contentSizeDidChangeNotification 通知: 用户更改了系统默认字体,比如 放大模式 会发送这个通知
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(contentSizeDidChangeNotification:)
     name:UIContentSizeCategoryDidChangeNotification
     object:nil];
}

- (void)dealloc{
    [[NSNotificationCenter defaultCenter]
     removeObserver:self];
}

/// 父类接收通知 子类去实现方法, 适合所有控制器都要实现某个通知的例子
/// 这个方法 设为public
-(void)contentSizeDidChangeNotification:(NSNotification*)notification{
    /// UIContentSizeCategoryNewValueKey
    /// 用户更改了系统默认字体大小 具体字体大小值
    [self contentSizeDidChange:notification.userInfo[UIContentSizeCategoryNewValueKey]];
}

-(void)contentSizeDidChange:(NSString *)size{
    //Implement in subclass
}

@end
