#pragma once
#include <inflection/api.h>
#include <unicode/utypes.h>

/**
 * @brief C API for dictionary morphological analysis and ambiguity detection.
 *
 * This module provides functions to detect grammatical ambiguity in words by
 * enumerating all possible interpretations (grammeme sets) a word form can have.
 *
 * A word is considered ambiguous if it has multiple valid grammatical interpretations.
 * For example, in German "die" can be:
 *   - nominative singular feminine article
 *   - accusative singular feminine article
 *   - nominative plural article
 *   - accusative plural article
 */


/**
 * Get all possible grammatical interpretations of a word.
 *
 * This function returns all distinct grammeme sets that the word could represent
 * according to the dictionary and inflection patterns for the locale.
 *
 * Each grammeme set represents one possible reading, with all grammatical
 * features encoded as a bitmask (POS, gender, number, case, etc.).
 *
 * Two-pass pattern:
 * 1. Call with results=NULL and resultsCapacity=0 to get the count
 * 2. Allocate array with that count, call again to fill it
 *
 * If the return value > 1, the word is grammatically ambiguous.
 * If the return value == 0, the word is unknown in the dictionary.
 *
 * @param locale BCP 47 locale string (e.g. "en", "de", "ru").
 * @param word UTF-16 word to analyze.
 * @param wordLen Length of word in char16_t units, or -1 for NULL-terminated.
 * @param results Output array to fill with grammeme sets (can be NULL for probe pass).
 * @param resultsCapacity Capacity of results array.
 * @param status UErrorCode.
 * @return Number of interpretations found (0 if unknown word, -1 on error).
 *
 * Example:
 *     // Probe pass
 *     int32_t count = dem_getWordGrammemeSets("de", u"die", -1, NULL, 0, &status);
 *     if (count > 1) {
 *         // Word is ambiguous — allocate and get details
 *         int64_t* sets = malloc(count * sizeof(int64_t));
 *         dem_getWordGrammemeSets("de", u"die", -1, sets, count, &status);
 *         // Use iddmd_getPropertyName to decode each grammeme bitmask
 *     }
 */
INFLECTION_CAPI int32_t dem_getWordGrammemeSets(
    const char* locale,
    const char16_t* word, int32_t wordLen,
    int64_t* results, int32_t resultsCapacity,
    UErrorCode* status);

/**
 * Get all possible inflections in the inflection paradigm(s) of a word.
 *
 * This function enumerates ALL forms in the word's inflection pattern, not just
 * interpretations of the given surface form. For example, "gato" would return
 * grammeme sets for both singular ("gato") and plural ("gatos") forms. In constrast, 
 * dem_getWordGrammemeSets bases on the word you supply and sees whether there are available sets from that word.
 *
 * This is useful for determining which grammatical dimensions can vary for a word.
 *
 * Two-pass pattern:
 * 1. Call with results=NULL and resultsCapacity=0 to get the count
 * 2. Allocate array with that count, call again to fill it
 *
 * @param locale BCP 47 locale string (e.g. "en", "es", "de").
 * @param word UTF-16 word to analyze.
 * @param wordLen Length of word in char16_t units, or -1 for NULL-terminated.
 * @param results Output array to fill with grammeme sets (can be NULL for probe pass).
 * @param resultsCapacity Capacity of results array.
 * @param status UErrorCode.
 * @return Number of inflections found (0 if unknown word, -1 on error).
 *
 * Example:
 *     // Get all forms in the paradigm for "gato"
 *     int32_t count = dem_getWordParadigmGrammemes("es", u"gato", -1, NULL, 0, &status);
 *     // count might be 2 (singular + plural)
 *     int64_t* sets = malloc(count * sizeof(int64_t));
 *     dem_getWordParadigmGrammemes("es", u"gato", -1, sets, count, &status);
 *     // sets[0] = grammemes for singular, sets[1] = grammemes for plural
 */
INFLECTION_CAPI int32_t dem_getWordParadigmGrammemes(
    const char* locale,
    const char16_t* word, int32_t wordLen,
    int64_t* results, int32_t resultsCapacity,
    UErrorCode* status);

