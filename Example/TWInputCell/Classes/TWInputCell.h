//
//  TWInputCell.h
//  TWInputCell_Example
//
//  Created by TW on 2021/3/17.
//  Copyright © 2021 tanwang11. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TWInputCellTool.h"


NS_ASSUME_NONNULL_BEGIN

static int TWInputInnerGap = 5;
#define TWInputLbtTfGap (TWInputInnerGap*2+1)

typedef NS_OPTIONS(NSUInteger, TWInputCellType) {
    TWInputCellTypeLBT      = 1 << 0,
    TWInputCellTypeLineView = 1 << 1,
    TWInputCellTypeRBT      = 1 << 2,
    TWInputCellTypeTextView = 1 << 3, // TextView 与 textFiled, textView暂且不支持TWInputTfType.
};

typedef NS_ENUM(int, TWInputTfType) {
    TWInputTfTypeNumberInt = 1, // 只限制数字输入,不进行format操作
    TWInputTfTypeNumberFloat, // 只限制数字输入,不进行format操作
    TWInputTfTypePassword,
    TWInputTfTypePhone,// 采用888-8888-8888约束
    TWInputTfTypeMoneyInt,// 采用100 0000,小数点为分界线
    TWInputTfTypeMoneyFloat,// 采用100 0000.0001,小数点为分界线
    TWInputTfTypeBank,// 采用6266 8888 8888 88,第一位为分界线
    TWInputTfTypeIdcard,// 采用123456 2000 0101 000X格式
};

@class TWInputCell;

typedef void(^TWInputCellBlock)       (TWInputCell * piCell);
typedef BOOL(^TWInputBoolCellBlock)   (TWInputCell * piCell); // 需要返回BOOL
typedef void(^TWInputCellIntBlock)    (TWInputCell * piCell, int intValue);
typedef void(^TWInputCellStringBlock) (TWInputCell * piCell, NSString * string);


@interface TWInputCell : UITableViewCell

@property (nonatomic, strong) UIButton    * lBT;
@property (nonatomic, strong) UIView      * lineView;
@property (nonatomic, strong) UITextField * tf;
@property (nonatomic, strong) UIButton    * rBT;

@property (nonatomic, strong) UIView      * view1;
@property (nonatomic, strong) UIView      * view2;
@property (nonatomic, strong) UIView      * view3;
@property (nonatomic, strong) UIView      * view4;

/*
 如果size.width <= 0,则设置为自动宽度;
 如果size.width <  0,则设置make.width.mas_lessThanOrEqualTo(-size.width);
 
 1问题: size.width == 0,适用于纯文本显示.假如用于文本输入输入框的可点击区域比较小,没有设置placeholder的话可能无法使用;
 假如是电话号码输入框,而且是靠右布局,那么会发生显示不完全问题,可以设置size.width<0,或者更新masonry布局;
 
 */
@property (nonatomic        ) CGSize      lbtSize;
@property (nonatomic        ) CGSize      rbtSize;

@property (nonatomic        ) int         lGap; // 最左边元素到cell边界
@property (nonatomic        ) int         rGap; // 最右边元素到cell边界
@property (nonatomic        ) int         cellH;
@property (nonatomic        ) int         tfH;

@property (nonatomic        ) int         textGapUnit; //钱数字间隔,一般为3|4

@property (nonatomic        ) int         timerRecord; // 一个timer计时器

@property (nonatomic        ) TWInputCellType cellType;
@property (nonatomic        ) TWInputTfType   tfType;

// 是否允许编辑TFblock
@property (nonatomic, copy  ) TWInputBoolCellBlock   editTFEnableBlock;

// TF编辑实时反馈block
@property (nonatomic, copy  ) TWInputCellStringBlock editTFBlock;

// TF编辑清除block
@property (nonatomic, copy  ) TWInputCellBlock       clearTFBlock;

@property (nonatomic, copy  ) TWInputCellBlock       rbtActionBlock;

// 自定义block,方便开发
@property (nonatomic, copy  ) TWInputCellBlock       customeBlock1;
@property (nonatomic, copy  ) TWInputCellBlock       customeBlock2;
@property (nonatomic, copy  ) TWInputCellBlock       customeBlock3;
@property (nonatomic, copy  ) TWInputCellBlock       customeBlock4;
@property (nonatomic, copy  ) TWInputCellBlock       customeBlock5;
@property (nonatomic, copy  ) TWInputCellBlock       customeBlock6;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier cellType:(TWInputCellType)cellType lbtSize:(CGSize)lbtSize rbtSize:(CGSize)rbtSize;

/**
 *  设置个人信息
 *
 *  @param lGap 推荐使用 [TWInputCellTool share].separatorInsetX
 *  @param rGap 习惯上lGap = rGap
 *
 *  @return id
 */
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier cellType:(TWInputCellType)cellType lbtSize:(CGSize)lbtSize rbtSize:(CGSize)rbtSize lGap:(int)lGap rGap:(int)rGap;


/**
 *  设置个人信息
 *
 *  @param lGap 推荐使用 [TWInputCellTool share].separatorInsetX
 *  @param rGap 习惯上lGap = rGap
 *  @param cellH 适用于 tableView: estimatedHeightForRowAtIndexPath:
 *  @param tfH 适用于 tableView: estimatedHeightForRowAtIndexPath:, 如果<=0 则等于cellH
 *  @return id
 */
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier cellType:(TWInputCellType)cellType lbtSize:(CGSize)lbtSize rbtSize:(CGSize)rbtSize lGap:(int)lGap rGap:(int)rGap cellH:(int)cellH tfH:(int)tfH;

- (void)setDefaultFetchCodeBT;
- (void)startTimerFrom:(int)max progress:(TWInputCellIntBlock)progressBlock finish:(TWInputCellBlock)finishBlock;
- (void)stopBTTimer;

// 普通数字
- (void)setTfTypeNumberInt;
- (void)setTfTypeNumberFloat;

- (void)setTfTypePhone;

// 金钱格式
- (void)setTfTypeMoneyFloat;
- (void)setTfTypeMoneyInt;

// 密码
- (void)setTfTypePassword;

// 银行卡格式
- (void)setTfTypeBank;

// 省份证格式, 假如输入达到17位的时候,会自动检查最后一位是否应该为X,假如是则自动补填X.
- (void)setTfTypeIdcard;

// 最大输入数字限制
- (void)setMaxLength:(int)maxLength maxBlock:(TWInputCellIntBlock)maxBlock;

@end

NS_ASSUME_NONNULL_END
