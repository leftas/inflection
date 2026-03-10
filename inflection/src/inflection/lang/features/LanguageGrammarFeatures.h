#pragma once
#include <inflection/api.h>
#include <unicode/utypes.h>

/**
 * @brief C API for querying grammar categories and their grammeme values per locale.
 *
 * A grammar category (e.g. "number") groups a set of grammeme values (e.g. "singular",
 * "plural"). This API lets callers enumerate all categories and their grammemes for a
 * given locale, which is useful for building a grammeme→category reverse map needed
 * by SemanticFeatureConcept constraint functions (putConstraintByName).
 *
 * Category ordering is alphabetical (consistent across calls).
 * The category list includes both common categories (shared by all locales, e.g. "pos",
 * "sound") and language-specific categories.
 */

/**
 * Return the total number of grammar categories for the given locale.
 * @param locale BCP 47 locale string (e.g. "en", "de", "ru").
 * @param status UErrorCode; set to failure if locale is unknown.
 * @return Number of categories, or -1 on error.
 */
INFLECTION_CAPI int32_t ilgf_getCategoryCount(const char* locale, UErrorCode* status);

/**
 * Return the name of the grammar category at the given index.
 * Categories are ordered alphabetically. Index must be in [0, getCategoryCount).
 * @param locale BCP 47 locale string.
 * @param categoryIndex Zero-based index of the category.
 * @param dest Output buffer for the UTF-16 category name.
 * @param destCapacity Capacity of dest in char16_t units.
 * @param status UErrorCode.
 * @return Length of the result string (may exceed destCapacity — use two-pass pattern).
 */
INFLECTION_CAPI int32_t ilgf_getCategoryName(const char* locale, int32_t categoryIndex,
                                              char16_t* dest, int32_t destCapacity,
                                              UErrorCode* status);

/**
 * Return the number of grammeme values for the named category.
 * @param locale BCP 47 locale string.
 * @param categoryName UTF-16 category name (e.g. u"number").
 * @param categoryNameLen Length of categoryName, or -1 for NUL-terminated.
 * @param status UErrorCode; set to failure if category not found.
 * @return Number of grammemes, or -1 on error.
 */
INFLECTION_CAPI int32_t ilgf_getGrammemeCount(const char* locale,
                                               const char16_t* categoryName, int32_t categoryNameLen,
                                               UErrorCode* status);

/**
 * Return the grammeme value at the given index within a named category.
 * @param locale BCP 47 locale string.
 * @param categoryName UTF-16 category name.
 * @param categoryNameLen Length of categoryName, or -1 for NUL-terminated.
 * @param grammemeIndex Zero-based index within the category's value set.
 * @param dest Output buffer for the UTF-16 grammeme name.
 * @param destCapacity Capacity of dest in char16_t units.
 * @param status UErrorCode.
 * @return Length of the result string (may exceed destCapacity — use two-pass pattern).
 */
INFLECTION_CAPI int32_t ilgf_getGrammemeName(const char* locale,
                                              const char16_t* categoryName, int32_t categoryNameLen,
                                              int32_t grammemeIndex,
                                              char16_t* dest, int32_t destCapacity,
                                              UErrorCode* status);
