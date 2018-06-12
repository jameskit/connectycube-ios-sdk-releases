//
//  CYBChatAttachment.h
//  ConnectyCube
//
//  Copyright © 2018 ConnectyCube. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(ChatAttachment)
@interface CYBChatAttachment : NSObject <NSSecureCoding, NSCopying>

/**
 Attachment name.
 */
@property (nonatomic, copy, nullable ) NSString *name;

/**
 Type of attachment.
 
 @discussion Can be any type. For example: audio, video, image, location, any other
 */
@property (nonatomic, copy, nullable) NSString *type;

/**
 Content URL.
 */
@property (nonatomic, copy, nullable) NSString *url;

/**
  ID of attached element.
 */
@property (nonatomic, copy, nullable) NSString *ID;


@property (nonatomic, strong, readonly, nullable) NSDictionary<NSString *, NSString *> *customParameters;

//MARK: Keyed subscripting for customParameters

- (nullable NSString *)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(nullable NSString *)obj forKeyedSubscript:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
