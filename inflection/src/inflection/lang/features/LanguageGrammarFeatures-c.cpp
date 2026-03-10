#include <inflection/lang/features/LanguageGrammarFeatures.h>
#include <inflection/lang/features/LanguageGrammarFeatures.hpp>
#include <inflection/util/TypeConversionUtils.hpp>
#include <inflection/util/ULocale.hpp>
#include <inflection/util/Validate.hpp>
#include <inflection/npc.hpp>
#include <unicode/ustring.h>

using ::inflection::lang::features::LanguageGrammarFeatures;
using ::inflection::util::TypeConversionUtils;

static auto getCategories(const char* locale)
{
    return LanguageGrammarFeatures::getLanguageGrammarFeatures(
            inflection::util::ULocale(npc(locale))).getCategories();
}

INFLECTION_CAPI int32_t ilgf_getCategoryCount(const char* locale, UErrorCode* status)
{
    if (status != nullptr && U_SUCCESS(*status)) {
        try {
            auto categories = getCategories(locale);
            return static_cast<int32_t>(categories.size());
        }
        catch (const ::std::exception& e) {
            TypeConversionUtils::convert(e, status);
        }
    }
    return -1;
}

INFLECTION_CAPI int32_t ilgf_getCategoryName(const char* locale, int32_t categoryIndex,
                                              char16_t* dest, int32_t destCapacity,
                                              UErrorCode* status)
{
    if (status != nullptr && U_SUCCESS(*status)) {
        try {
            inflection::util::Validate::isTrue(categoryIndex >= 0);
            auto categories = getCategories(locale);
            inflection::util::Validate::isTrue(categoryIndex < static_cast<int32_t>(categories.size()));
            auto it = categories.begin();
            std::advance(it, categoryIndex);
            const auto& name = it->first;
            auto resultLen = static_cast<int32_t>(name.length());
            if (destCapacity > 0 && resultLen < destCapacity) {
                u_strncpy((UChar*)dest, (const UChar*)name.c_str(), resultLen);
            }
            return TypeConversionUtils::terminateString(dest, destCapacity, resultLen, status);
        }
        catch (const ::std::exception& e) {
            TypeConversionUtils::convert(e, status);
        }
    }
    return -1;
}

INFLECTION_CAPI int32_t ilgf_getGrammemeCount(const char* locale,
                                               const char16_t* categoryName, int32_t categoryNameLen,
                                               UErrorCode* status)
{
    if (status != nullptr && U_SUCCESS(*status)) {
        try {
            inflection::util::Validate::notNull(categoryName);
            ::std::u16string_view catView = categoryNameLen < 0
                ? ::std::u16string_view(categoryName)
                : ::std::u16string_view(categoryName, categoryNameLen);
            auto categories = getCategories(locale);
            auto it = categories.find(::std::u16string(catView));
            inflection::util::Validate::isTrue(it != categories.end(),
                                               u"Category not found");
            return static_cast<int32_t>(it->second.getValues().size());
        }
        catch (const ::std::exception& e) {
            TypeConversionUtils::convert(e, status);
        }
    }
    return -1;
}

INFLECTION_CAPI int32_t ilgf_getGrammemeName(const char* locale,
                                              const char16_t* categoryName, int32_t categoryNameLen,
                                              int32_t grammemeIndex,
                                              char16_t* dest, int32_t destCapacity,
                                              UErrorCode* status)
{
    if (status != nullptr && U_SUCCESS(*status)) {
        try {
            inflection::util::Validate::notNull(categoryName);
            inflection::util::Validate::isTrue(grammemeIndex >= 0);
            ::std::u16string_view catView = categoryNameLen < 0
                ? ::std::u16string_view(categoryName)
                : ::std::u16string_view(categoryName, categoryNameLen);
            auto categories = getCategories(locale);
            auto it = categories.find(::std::u16string(catView));
            inflection::util::Validate::isTrue(it != categories.end(),
                                               u"Category not found");
            const auto values = it->second.getValues(); // ordered set
            inflection::util::Validate::isTrue(grammemeIndex < static_cast<int32_t>(values.size()));
            auto vit = values.begin();
            std::advance(vit, grammemeIndex);
            const auto& grammeme = *vit;
            auto resultLen = static_cast<int32_t>(grammeme.length());
            if (destCapacity > 0 && resultLen < destCapacity) {
                u_strncpy((UChar*)dest, (const UChar*)grammeme.c_str(), resultLen);
            }
            return TypeConversionUtils::terminateString(dest, destCapacity, resultLen, status);
        }
        catch (const ::std::exception& e) {
            TypeConversionUtils::convert(e, status);
        }
    }
    return -1;
}
