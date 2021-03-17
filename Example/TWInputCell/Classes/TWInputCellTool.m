//
//  TWInputCellTool.m
//  TWInputCell_Example
//
//  Created by TW on 2021/3/17.
//  Copyright © 2021 tanwang11. All rights reserved.
//

#import "TWInputCellTool.h"

@implementation TWInputCellTool

+ (instancetype)share {
    static dispatch_once_t once;
    static TWInputCellTool * instance;
    dispatch_once(&once, ^{
        instance = [self new];
        
        instance.separatorInsetX = 15;
        if ([[UIScreen mainScreen] bounds].size.width == 414) {
            instance.separatorInsetX = 20;
        }
    });
    return instance;
}

@end
