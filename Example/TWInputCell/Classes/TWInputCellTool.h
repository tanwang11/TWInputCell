//
//  TWInputCellTool.h
//  TWInputCell_Example
//
//  Created by TW on 2021/3/17.
//  Copyright © 2021 tanwang11. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface TWInputCellTool : NSObject

// 据测试,只有iPhone6plus的x是20,其他都是15.
@property (nonatomic        ) float separatorInsetX;

+ (instancetype)share;


@end

NS_ASSUME_NONNULL_END
